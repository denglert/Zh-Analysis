SIM_FILE_PATH = ~/lib/projects/2HDM/MadGraph/gg_z_mumuh_LoopInd/Events/run_10kEv_decayed_1/tag_1_delphes_events.root

run : build
	@./bin/Zh-Analyzer $(SIM_FILE_PATH)

test :
	@ echo "Test."

###############################

build : 
	@ cd src; make all 
