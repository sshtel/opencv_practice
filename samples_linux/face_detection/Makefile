PROJECT=face_detection

CC=arm-linux-gnueabihf-gcc
CXX=arm-linux-gnueabihf-g++

PLATFORM=arm_linux

ROOT_DIR=../..
CV_INC_DIR=$(ROOT_DIR)/opencv/include
CV_LIB_DIR=$(ROOT_DIR)/opencv/$(PLATFORM)/lib

SRC_DIR=$(ROOT_DIR)/src

CFLAGS+=-I$(CV_INC_DIR)
CFLAGS+=-I$(SRC_DIR)
CFLAGS+=-I$(SRC_DIR)/$(PROJECT)

LDFLAGS+=-L$(CV_LIB_DIR)
LDFLAGS+=-lopencv_core
LDFLAGS+=-lopencv_highgui
LDFLAGS+=-lopencv_ocl
LDFLAGS+=-lopencv_imgproc
LDFLAGS+=-lopencv_objdetect


HDRS=

SRCS+=Main.cpp
SRCS+=WorkThreadLinux.cpp
SRCS+=$(SRC_DIR)/device_ocl.cpp
SRCS+=$(SRC_DIR)/$(PROJECT)/FaceDetectorCL.cpp  
SRCS+=$(SRC_DIR)/$(PROJECT)/FaceDetector.cpp
SRCS+=$(SRC_DIR)/$(PROJECT)/FaceDetectorCpu.cpp


OUTPUT=$(PROJECT)



all:
	$(CXX) $(SRCS) $(HDRS) $(LDFLAGS) $(CFLAGS) -o $(OUTPUT)
