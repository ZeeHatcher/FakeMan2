SRCDIR="./FakeMan2"
OUTDIR="./Debug"

./clean.sh

echo "Building source..."

mkdir -p $OUTDIR
skm clang++ ${SRCDIR}/*.cpp -o ${OUTDIR}/FakeMan2

echo "Build finished..."
