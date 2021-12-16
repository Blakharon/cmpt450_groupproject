#!/bin/bash
FLAGS="NoncoherentDma"
#FLAGS="HWACC,LLVMRuntime,LLVMInterface,DeviceMMR,NoncoherentDma"
#FLAGS="HWACC"
BENCH=""
DEBUG="false"
PRINT_TO_FILE="false"
TYPE="cache"

# Input file paths relative to the base repo.
INPUT="inputs/mnist/bin/circle_25x25_0.bin"
M0="inputs/mnist/bin/m0.bin"
M1="inputs/mnist/bin/m1.bin"
MASK="inputs/mnist/bin/circle_mask_25x25.bin"

while getopts "t:b:f:dp" opt
	do
		case $opt in
			t )
				TYPE=${OPTARG}
				;;
			b )
				BENCH=${OPTARG}
				;;
			d )
				DEBUG="true"
				;;
			p )
				PRINT_TO_FILE="true"
				;;
			f )
				FLAGS+=",${OPTARG}"
				;;
			* )
				echo "Invalid argument: ${OPTARG}"
				echo "Usage: $0 -t [model] -b BENCHMARK [flow] (-f DEBUGFLAG) (-p) (-d)"
				exit 1
				;;
		esac
done

if [ "${TYPE}" == "" ]; then
	echo "No benchmark specified."
	echo "Usage: $0 -t [cache/dma] -b BENCHMARK (-f DEBUGFLAG) (-p) (-d)"
	exit 2
fi

if [ "${BENCH}" == "" ]; then
	echo "No benchmark specified."
	echo "Usage: $0 -t [cache/dma] -b BENCHMARK (-f DEBUGFLAG) (-p) (-d)"
	exit 2
fi

if [ "${DEBUG}" == "true" ]; then
	BINARY="ddd --gdb --args ${M5_PATH}/build/ARM/gem5.debug"
else
	BINARY="${M5_PATH}/build/ARM/gem5.opt"
fi

KERNEL=$LAB_PATH/$TYPE/$BENCH/host/main.elf
SYS_OPTS="--mem-size=8GB \
          --kernel=$KERNEL \
          --disk-image=$M5_PATH/baremetal/common/fake.iso \
          --machine-type=VExpress_GEM5_V1 \
          --dtb-file=none --bare-metal \
          --cpu-type=MinorCPU"
CACHE_OPTS="--caches --l2cache"
# Script to start up full system simulation
# --debug-flags=$FLAGS

OUTDIR=BM_MODEL/$BENCH

RUN_SCRIPT="$BINARY --debug-flags=$FLAGS --outdir=$OUTDIR \
			gem5-config/run_mnist.py $SYS_OPTS \
			--accpath=$LAB_PATH/$TYPE \
			--accbench=$BENCH $CACHE_OPTS \
			--input $INPUT --mask $MASK"

if [ "${PRINT_TO_FILE}" == "true" ]; then
	mkdir -p $OUTDIR
	$RUN_SCRIPT > ${OUTDIR}/debug-trace.txt
else
	$RUN_SCRIPT
fi

# Debug Flags List
#
# IOAcc
# ClassDetail
# CommInterface
# ComputeUnit
# LLVMInterface
# ComputeNode
# LLVMRegister
# LLVMOp
# LLVMParse
# LLVMGEP
# LLVMRuntime == ComputeNode + LLVMRegister + LLVMOp + LLVMParse
# NoncoherentDma - bfs, fft, gemm, md-knn, nw, spmv


