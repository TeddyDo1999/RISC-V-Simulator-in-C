SOURCE1 := Main.c Parser.c Registers.c Core.c Branch.c Controller.c Data_Memory.c Decoder.c Imm_Gen.c ALU_Control.c
SOURCE2 := Main2.c Parser.c Registers.c Core.c Branch.c Controller.c Data_Memory.c Decoder.c Imm_Gen.c ALU_Control.c
VIEWER = less
CC	:= gcc
TARGET1	:= RVSim1
TARGET2	:= RVSim2
EXECUTABLES := Main Parser Imm_Gen Branch Data_Memory Core Controller 

.PHONY: basic_sim extra_credit clean


basic_sim: $(SOURCE1)
	$(CC) -o $(TARGET1) $(SOURCE1)
	chmod u+x $(TARGET1)  
	./$(TARGET1) example_cpu_trace

extra_credit: $(SOURCE2)
	$(CC) -o $(TARGET2) $(SOURCE2)
	chmod u+x $(TARGET2)  
	./$(TARGET2) extra_credit_code

clean_executables:  
	rm $(EXECUTABLES)
	