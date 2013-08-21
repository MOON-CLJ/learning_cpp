default:
	g++ multi_ldb_exporter_step1.cc -o multi_ldb_exporter_step1 constants.h utils.h utils.cc comparators.h comparators.cc /usr/local/lib/libleveldb.a /usr/local/lib/libsnappy.a -lpthread -lboost_system-mt -lboost_filesystem-mt
	g++ multi_ldb_exporter_step2.cc -o multi_ldb_exporter_step2 constants.h utils.h utils.cc comparators.h comparators.cc /usr/local/lib/libleveldb.a /usr/local/lib/libsnappy.a -lpthread -lboost_system-mt -lboost_filesystem-mt
