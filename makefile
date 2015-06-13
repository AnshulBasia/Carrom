# Default case (user-side)
PROJ_HOME ?= $(CURDIR)

# Project specific
NAME := carrom
SOURCES_LIST := gamestate.cpp main.cpp piece.cpp render_engine.cpp renderstate.cpp  
INCLUDE_LIST := gamestate.h  piece.h  render_engine.h  renderstate.h
MAKE_FILE := $(CURDIR)/$(lastword $(MAKEFILE_LIST))
USER := $(shell whoami)_$(shell date +"%j%H%M%S")
TMP_DIR := /tmp/$(USER)

# targets
all: build


build:
	g++ -I./include src/*.cpp -lGL -lglut -o carrom

clean:
	rm -f carrom

run:
	@echo "Running the program"
	@./carrom &> /dev/null

debug-run:
	@echo "Running the program"
	@./carrom

tests:
	@echo 'No automated test-cases. Grading based on visual inspection of simulation'

submit: clean
	@echo 'Generating ZIP file to upload'
	@mkdir $(TMP_DIR)
	@cp -r ../$(NAME) $(TMP_DIR)
	@rm -rf $(TMP_DIR)/$(NAME)/tests $(TMP_DIR)/$(NAME)/makefile $(TMP_DIR)/$(NAME)/verifier $(TMP_DIR)/$(NAME)/$(NAME).zip $(TMP_DIR)/$(NAME)/.cproject $(TMP_DIR)/$(NAME)/*.pdf
	@cd $(TMP_DIR); zip -r $(NAME).zip $(NAME); cd $(PROJ_HOME)
	@mv -f $(TMP_DIR)/$(NAME).zip .
	@rm -rf $(TMP_DIR)	

submit.practice: submit
	@echo 'Upload $(NAME).zip to https://10.237.20.228:1345/OnlineEvaluation/default/submit for a practice run'

submit.grade: submit
	@echo 'Upload $(NAME).zip to https://10.237.20.241:1345/OnlineEvaluation/default/submit to complete submission'

