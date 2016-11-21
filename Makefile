## qq_Zh tree level

# SM - gg_qq_mummuph
#RUN_ZH_ANA_TAG        = SM-gg_qq-mummuph
#RUN_ZH_ANA_BINCONFIG  = ./config/bin.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_SM_gg_qq_Zh.conf
#RUN_ZH_ANA_nEvents    = -1

# 2HDM
#RUN_ZH_ANA_TAG        = test_2HDM
#RUN_ZH_ANA_BINCONFIG  = ./config/bin.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_2HDM.conf
#RUN_ZH_ANA_nEvents    = -1

# SM - Signal + bkgr
#RUN_ZH_ANA_TAG        = signal_with_bkgr
#RUN_ZH_ANA_BINCONFIG  = ./config/bin.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_with_bkgr.conf
#RUN_ZH_ANA_nEvents    = -1

# SM - ggZh, box interference triangle
#RUN_ZH_ANA_TAG        = SM_ggZh_box_int_tri
#RUN_ZH_ANA_BINCONFIG  = ./config/bin.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_SM_box_int_tri.conf
#RUN_ZH_ANA_nEvents    = -1

# 2HDMtII - ggZh all
#RUN_ZH_ANA_TAG        = 2HDMtII_NLO_gg_lmlph_all
#RUN_ZH_ANA_BINCONFIG  = ./config/bin.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_2HDM.conf
#RUN_ZH_ANA_nEvents    = -1

# Test
#RUN_ZH_ANA_TAG        = SM_gg_Zh_parton_level
##RUN_ZH_ANA_TAG        = 2HDMtII_gg_Zh_parton_level
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_test.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_test.conf
#RUN_ZH_ANA_nEvents    = -1

# - SM: qq + gg -> Zh
#RUN_ZH_ANA_TAG        = SM_qq_gg_Zh_parton_level
##RUN_ZH_ANA_TAG        = 2HDMtII_gg_Zh_parton_level
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_parton_level.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_SM_qq_gg_Zh_parton_level.conf
#RUN_ZH_ANA_nEvents    = -1

# - 2HDMtII: qq + gg -> Zh mA = 180
#RUN_ZH_ANA_TAG        = 2HDMtII_mA_180_qq_gg_Zh_parton_level
##RUN_ZH_ANA_TAG        = 2HDMtII_gg_Zh_parton_level
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_parton_level.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_2HDMtII_B1_mA_180_qq_gg_Zh_parton_level.conf
#RUN_ZH_ANA_nEvents    = -1


# - 2HDMtII: qq + gg -> Zh mA = 200
#RUN_ZH_ANA_TAG        = 2HDMtII_mA_200_qq_gg_Zh_parton_level
##RUN_ZH_ANA_TAG        = 2HDMtII_gg_Zh_parton_level
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_parton_level.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_2HDMtII_B1_mA_200_qq_gg_Zh_parton_level.conf
#RUN_ZH_ANA_nEvents    = -1

# - 2HDMtII: qq + gg -> Zh mA = 200
#RUN_ZH_ANA_TAG        = 2HDMtII_mA_220_qq_gg_Zh_parton_level
##RUN_ZH_ANA_TAG        = 2HDMtII_gg_Zh_parton_level
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_parton_level.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_2HDMtII_B1_mA_220_qq_gg_Zh_parton_level.conf
#RUN_ZH_ANA_nEvents    = -1

# - MWTC test
#RUN_ZH_ANA_TAG        = MWTC_test
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_MWTC_parton_level.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_MWTC_default.conf
#RUN_ZH_ANA_nEvents    = -1

# - SM pp Zh default
#RUN_ZH_ANA_TAG        = SM_pp_Zh_default
#RUN_ZH_ANA_BINCONFIG  = ./config/bin_parton_level.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp_SM_ppZh_default.conf
#RUN_ZH_ANA_nEvents    = -1

# gg_Zh LoopInd
#RUN_ZH_ANA_TAG       = gg_Zh_LoopInd
#RUN_ZH_ANA_FILE_PATH = ~/lib/projects/2HDM/MadGraph/gg_z_mumuh_LoopInd/Events/run_10kEv_decayed_1/tag_1_delphes_events.root
#RUN_ZH_ANA_CONFIG    = ./config/default.conf
#RUN_ZH_ANA_nEvents   = -1

# gg_Zh LoopInd
#RUN_ZH_ANA_TAG        = gg_qq_zh
#RUN_ZH_ANA_BINCONFIG  = ./config/bin.conf
#RUN_ZH_ANA_COMPCONFIG = ./config/comp.conf
#RUN_ZH_ANA_nEvents    = -1

VAR_RUN_ZH_ANA    = $(shell echo '$(.VARIABLES)' |  awk -v RS=' ' '/RUN_ZH_ANA_/' | sed 's/RUN_ZH_ANA_//g' )
EXPORT_RUN_ZH_ANA = $(foreach v,$(VAR_RUN_ZH_ANA),$(v)="$(RUN_ZH_ANA_$(v))")

all :

Ana-Zh : build
	@$(EXPORT_RUN_ZH_ANA) ./scripts/createWD.sh
	@./bin/Zh-Analyzer $(RUN_ZH_ANA_TAG) $(RUN_ZH_ANA_COMPCONFIG) $(RUN_ZH_ANA_BINCONFIG) $(RUN_ZH_ANA_nEvents)

Ana-Zh-parton: build
	@$(EXPORT_RUN_ZH_ANA) ./scripts/createWD.sh
	@./bin/Zh-Parton-Analyzer $(RUN_ZH_ANA_TAG) $(RUN_ZH_ANA_COMPCONFIG) $(RUN_ZH_ANA_BINCONFIG) $(RUN_ZH_ANA_nEvents)


test :
	@ echo "Test."
	@ echo $(VAR_RUN_ZH_ANA)
	@ echo $(EXPORT_RUN_ZH_ANA)

###############################

build : 
	@ cd src; make all 

clean :
	rm ./lib/*
