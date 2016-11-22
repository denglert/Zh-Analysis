export ANALYSIS=Zh-PartonLevel
export TAG=test
export BINCONFIG=./config/bin.conf
export COMPCONFIG=./config/comp.conf
export nEvents=-1

make build ANALYSIS=${ANALYSIS}
./scripts/createWD.sh

echo ""
echo "-------------------------"
echo "Analysis:   ${ANALYSIS}"
echo "TAG:        ${TAG}"
echo "BINCONFIG:  ${BINCONFIG}"
echo "COMPCONFIG: ${BINCONFIG}"
echo "nEvents:    ${BINCONFIG}"
echo "-------------------------"
echo ""

./bin/RunAnalysis-${ANALYSIS} ${TAG} ${COMPCONFIG} ${BINCONFIG} ${nEvents}
