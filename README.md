# leveldb index demo
====================


## 1，需求
---------
user_profile项目
<table>
    <tr>
        <td>uid</td>
        <td>l1</td>
        <td>l2</td>
        <td>l3</td>
        <td>l4</td>
    </tr>
    <tr>
        <td>1001</td>
        <td>1</td>
        <td>1</td>
        <td></td>
        <td>1</td>
    </tr>
    <tr>
        <td>1002</td>
        <td>2</td>
        <td>1</td>
        <td>1</td>
        <td></td>
    </tr>
    <tr>
        <td>1003</td>
        <td>3</td>
        <td>3</td>
        <td>2</td>
        <td>1</td>
    </tr>
</table>
a，项目的输入数据就类似上表这样的很多个不同的稀疏表结构

b，每张表都非常大

c，要求对表按照uid做交、并、diff（在a中不在b中）

## 2，现状
---------
3月份，做过一个基于mongodb的实现，功能都能完全保证，但是性能、、、

然后目前数据组的做法是

原始数据文本文件 + dpark暴力筛

## 3，初步设想
------------
我先是查资料查了一周（培训剩的时间不多）

最后看到一篇http://rdc.taobao.com/blog/cs/?p=1394是介绍Tair是怎样使用leveldb的。

Tair是淘宝开源的分布式KV缓存系统

leveldb是Google开源的单机KV存储引擎。key是排序的，排序规则可自定义。

由此萌生了一个初步的设想

1中的表实际上可以这样存储

原始数据：
<table>
    <tr>
        <td>key</td>
        <td>value</td>
    </tr>
    <tr>
        <td>1001</td>
        <td>1\t1\t\t1</td>
    </tr>
    <tr>
        <td>1002</td>
        <td>2\t1\t1\t</td>
    </tr>
    <tr>
        <td>1003</td>
        <td>3\t3\t2\t1</td>
    </tr>
</table>
l2索引：
<table>
    <tr>
        <td>key</td>
        <td>value</td>
    </tr>
    <tr>
        <td>1_1001</td>
        <td>1001</td>
    </tr>
    <tr>
        <td>1_1002</td>
        <td>1002</td>
    </tr>
    <tr>
        <td>3_1003</td>
        <td>1003</td>
    </tr>
</table>
l3索引：
<table>
    <tr>
        <td>key</td>
        <td>value</td>
    </tr>
    <tr>
        <td>^_1001</td>
        <td>1001</td>
    </tr>
    <tr>
        <td>1_1002</td>
        <td>1002</td>
    </tr>
    <tr>
        <td>2_1003</td>
        <td>1003</td>
    </tr>
</table>
leveldb的性能非常好，但是同时只允许一个进程访问读写。

绕过这个问题的方式是，将数据存储在多个leveldb实例中，并对存储元信息进行管理。

对leveldb多个实例单独进行读写是可以并行的。

所以我的demo目前实现的

multi_ldb_exporter_step1.cc

a，先将原始数据集写入leveldb的单个实例中。

b，将a中的单个实例按照每固定数量一组拆分到多个实例中。

multi_ldb_exporter_step2.cc

c，再将更新数据集写入到拆分后形成的多个实例中。

d，将拆分后超过固定数量的实例继续拆分为多个实例。

## 写入和更新性能
---------------
localhost ssd

### 真实数据集global_activity 88.4M 100W条

每100000条拆为一个leveldb实例

row1

1000001 2006-01-09      100000000000000100000011000010  5       228     299     70      26      15      1585    543     263     59905   80      153     141     173     6261    203     10      32.8100 3  114.0

multi_ldb_exporter_step1.cc 89.5M

real    0m3.556s

user    0m2.707s

sys     0m0.468s

multi_ldb_exporter_step2.cc 115.3M(可compact)

real    0m7.671s

user    0m6.598s

sys     0m0.537s

### 伪造数据集 1.7G 1亿条

每1000W条拆为一个leveldb实例

row1

1 1

multi_ldb_exporter_step1.cc 1.7G

real    6m55.043s

user    5m3.929s

sys     0m39.468s

multi_ldb_exporter_step2.cc 2.5G(可compact)

real    11m15.649s

user    10m38.311s

sys     0m17.474s


### 伪造index数据集 100W(自定义的比较函数不同)

0_0▸0

1_1▸1

0_10▸---10

1_11▸---11

multi_ldb_exporter_step1.cc

real    0m8.565s

user    0m8.380s

sys     0m0.132s

## index查询
-----------
```
leveldb::Slice s_beg("8_^!");
  leveldb::Slice s_end("9_^!");
  for (it->Seek(s_beg); it->Valid() && cmp.Compare(it->key(), s_end) < 0; it->Next()) {
    cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
  }
```
```
results:

8_8!: 8

8_18!: 18

8_28!: 28

8_38!: 38

8_48!: 48

8_58!: 58

8_68!: 68

8_78!: 78

8_88!: 88

8_98!: 98

...
```
## demo实现的缺陷
---------------
a,

leveldb并不提供db.size()这样的接口，有一个issue提到过，作者的解释是在内部实现和外部实现这个功能是一样的代价。

所以在update里为了正确维护每个db的size这个信息，目前采取对于每个更新的key都查询一次，这也就是step2比step1慢的原因，不考虑这个因素的话，两者能达到同样的速度。

leveldb提供一个近似的磁盘占用大小的接口db->GetApproximateSizes,可以考虑用这个接口，用实际磁盘占用替代count来作为实例拆分的依据。本demo暂未实现。

b，

本demo主要是考察设想的可行性和性能问题，只做过少量场景数据的测试。

## 一点点c++性能优化和坑
---------------------
自定义比较函数

### 对于uid的比较函数

```
int NumericComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
  // Notice: 没考虑负数，也没考虑小数
  size_t a_len, b_len;
  a_len = a.size();
  b_len = b.size();
  if (a_len < b_len) return -1;
  if (a_len > b_len) return 1;
  return a.compare(b);
}
```

### 对于index的比较函数

```
int MultiNumericComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {
  const char* a_data = a.data();
  const char* b_data = b.data();
  char* a_data_next;
  char* b_data_next;

  while (1) {
    if (*a_data == idxLower || *b_data == idxUpper) return -1;
    if (*a_data == idxUpper || *b_data == idxLower) return 1;

    double d1, d2;
    d1 = strtod(a_data, &a_data_next);
    d2 = strtod(b_data, &b_data_next);

    if (d1 < d2) return -1;
    if (d1 > d2) return 1;

    if (*a_data_next == idxTerminated) break;
    a_data = ++a_data_next;
    b_data = ++b_data_next;
  }

  return 0;
}
```

比较函数在leveldb中用来比较判断key的大小，被非常频繁的调用，其性能非常重要。

```
class Slice {
public:
  // Create a slice that refers to d[0,n-1].
  Slice(const char* d, size_t n) : data_(d), size_(n) { }

  // Create a slice that refers to the contents of "s"
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) { }
  ...
private:
  const char* data_;
  size_t size_;
}；
inline int Slice::compare(const Slice& b) const {
  ...
  int r = memcmp(data_, b.data_, min_len);
  ... 
  return r;
}
```
即其比较操作是在内存中进行的，才能保证效率。

NumericComparator的实现很自然。

但是MultiNumericComparator最开始的实现是先逐字符添加到临时的字符串，在对临时字符串调用boost::lexical_cast，这样效果很差，将index的写入效率拉低了10倍，到20k/s的写入，请教changsheng后，才改成现在的strtod函数比较方法。小trick，strtod函数希望的是c风格字符串的参数，但是目前没有找到在slice的结尾添加一个'\0'的方法，所以用'!'替代。

### 坑
“hehe” + '!'

## 开发注意事项
-------------
g++ multi_ldb_exporter_step1.cc constants.h utils.h utils.cc comparators.h comparators.cc /usr/local/lib/libleveldb.a /usr/local/lib/libsnappy.a -lpthread -lboost_system-mt -lboost_filesystem-mt

## 结束语：我是怎么走上c++的道路的
-----------------------------
我爱上了c++，义无反顾。