export EVT_ANALYSIS=Zh-PartonLevel
#export MAIN_ANALYSIS=RunAnalysis
export MAIN_ANALYSIS=RunAnalysis-custom
export TAG=test
export BINCONFIG=./config/bin_test.conf
export COMPCONFIG=./config/comp_test.conf
export nEvents=-1

make build EVT_ANALYSIS=${EVT_ANALYSIS} MAIN_ANALYSIS=${MAIN_ANALYSIS}
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

./bin/${MAIN_ANALYSIS}-${EVT_ANALYSIS} ${TAG} ${COMPCONFIG} ${BINCONFIG} ${nEvents}
