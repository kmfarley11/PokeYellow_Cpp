# Script to build googletest source from Make file location
GTDIR=../deps/gtest/googletest
GMDIR=../deps/gtest/googlemock

# include ${GDIR}/include in the system header search path
# include ${GDIR} in the standard search path
g++ -isystem ${GTDIR}/include -I ${GTDIR} \
	-pthread -c ${GTDIR}/src/gtest-all.cc

# TODO: once a custom class has been created: build gmock 
#     and link it here for modular & easy class mocking
# g++ -isystem ${GTDIR}/include 

# create link for obj file
ar -rv libgtest.a gtest-all.o
rm gtest-all.o
