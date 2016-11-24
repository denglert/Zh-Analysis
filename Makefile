# - Test
RUN_ANALYSIS       = Zh-PartonLevel
RUN_ANA_TAG        = test
RUN_ANA_BINCONFIG  = ./config/bin_test.conf
RUN_ANA_COMPCONFIG = ./config/comp_test.conf
RUN_ANA_nEvents    = -1

VAR_RUN_ANA    = $(shell echo '$(.VARIABLES)' |  awk -v RS=' ' '/RUN_ANA_/' | sed 's/RUN_ANA_//g' )
EXPORT_RUN_ANA = $(foreach v,$(VAR_RUN_ANA),$(v)="$(RUN_ANA_$(v))")

all :

run: build_for_run
	@$(EXPORT_RUN_ANA) ./scripts/createWD.sh
	@./bin/RunAnalysis-$(RUN_ANALYSIS) $(RUN_ANA_TAG) $(RUN_ANA_COMPCONFIG) $(RUN_ANA_BINCONFIG) $(RUN_ANA_nEvents)


test :
	@ echo "Test."
	@ echo $(VAR_RUN_ANA)
	@ echo $(EXPORT_RUN_ANA)

###############################

build_for_run : 
	cd src; ANALYSIS=$(RUN_ANALYSIS) make all;

export $(ANALYSIS)

build : 
	@if [ -z $(ANALYSIS) ]; then\
		echo "ANALYSIS variable not defined";\
		echo "Please specify which analysis you want to compile.";\
		echo "e.g. make build ANALYSIS=Zh-PartonLevel";\
	 else\
	 cd src; make all; \
	 fi
	
clean :
	rm ./lib/*
