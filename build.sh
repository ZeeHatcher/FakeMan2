SRCDIR="./FakeMan2"
OUTDIR="./Debug"

mkdir -p $OUTDIR
skm clang++ ${SRCDIR}/*.cpp -o ${OUTDIR}/FakeMan2
