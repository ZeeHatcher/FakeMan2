find ./FakeMan2/* ! -name main.cpp -exec cp -t ./test/ {} +
skm clang++ ./test/*.cpp -o FakeMan2_test.exe
./FakeMan2_test.exe
