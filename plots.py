# Set the absolute path in 

import numpy as np
import pandas as pd
import seaborn as sea
from matplotlib import pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import os

sea.set()

datadir = os.getcwd()+'/outputs/'

all_accelerators = ["pl", "ek"]
accelerators = ["pl"]

all_image_sizes = ["25x25", "15x15", "5x5"]
image_sizes = ["25x25"]

all_images = ["circle0", "circle1", "circle2", "circle3", "circle4", "circle5"]
images = ["circle0", "circle1", "circle2", "circle3", "circle4", "circle5"];

all_benchmarks = ["Performance", "Stall_Cycles", "Energy"]
benchmarks = ["Performance", "Stall_cycles", "Energy"]

def getCSstat(filename, statsfile, accelerator, benchmark):
    filename = os.path.join(datadir, '', filename, statsfile).replace('\\','/')
    
    if (accelerator == "pl"):
        accelerator = "pushrelabel"
    else:
        accelerator = "edmondskarp"
    
    if (benchmark == "Performance"):
        with open(filename) as f:
            r = f.read()
            if len(r) < 10: return 0.0
            stat = "system.acctest."+accelerator+".compute\n   ========= Performance"
            if (r.find(stat) != -1) :
                start = r.find(stat)
                end = r.find("Runtime:", start)
                start = end
                end = r.find("Runtime:", start + 8)
                runtime = r[start:end]
                runtime = runtime[33:-11]
                return int(runtime)
            else:
                print("Stat not found")
                return 0
    elif (benchmark == "Stall_Cycles"):
        with open(filename) as f:
            r = f.read()
            if len(r) < 10: return 0.0
            stat = "system.acctest."+accelerator+".compute\n   ========= Performance"
            if (r.find(stat) != -1) :
                start = r.find(stat)
                start = r.find("Stalls:", start)
                end = r.find("Executed Nodes:", start)
                runtime = r[start:end]
                runtime = runtime[33:-11]
                return int(runtime)
            else:
                print("Stat not found")
                return 0
    elif (benchmark == "Energy"):
        with open(filename) as f:
            r = f.read()
            if len(r) < 10: return 0.0
            stat = "system.acctest."+accelerator+".compute\n   ========= Performance"
            if (r.find(stat) != -1) :
                start = r.find(stat)
                start = r.find("FU Total Power:", start)
                end = r.find("\n", start)
                runtime = r[start:end]
                runtime = runtime[33:-4]
                return float(runtime)
            else:
                print("Stat not found")
                return float(0.0)
    else:
        print("Invalid benchmark")

def performance_plots():
    plt.figure()
    fig = sea.barplot(x='Image Size', y='Runtime Cycles', data=df, hue="Algorithm", edgecolor="black", ci=None)
    plt.title("MaxFlow Runtime Performance")
    fig.legend(loc=(1.02, 0.6), title="Algorithm")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("MaxFlow Runtime Performance.png", format='png', dpi=600)

def q2_plots():
    dataq2 = df[(df["Accelerator"] == "top") & (df["Optimized"] == "Unoptimized") & (df["Model"] == "Cache")]
    dataq2["Compute Cycles"] = dataq2["Runtime Cycles"] - dataq2["Stall Cycles"]
    print("\nDataQ2:\n")
    print(dataq2)
    plt.figure()
    fig1 = sea.barplot(x='Cache Size', y='Stall Cycles', data=dataq2, hue="Loop Unroll Factor", edgecolor="black", ci=None, palette=["lightblue","bisque","lightgreen","lightcoral"])
    fig2 = sea.barplot(x='Cache Size', y='Compute Cycles', data=dataq2, hue="Loop Unroll Factor", edgecolor="black", ci=None)
    plt.ylabel("Compute and Stall Cycles")
    plt.title("Top Stall & Compute Cycles")
    fig1.legend(loc=(1.02, 0.4), title="Loop Unroll Factors")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top Stall & Compute Cycles.png", format='png', dpi=600)
    
def q3_plots():
    dataq3 = df[(df["Accelerator"] == "top") & (df["Optimized"] == "Unoptimized") & (df["Model"] == "Cache")]
    dataq3["Total Energy"] = dataq3["Energy"] * dataq3["Runtime Cycles"]
    print("\nDataQ3:\n")
    print(dataq3)
    plt.figure()
    fig = sea.scatterplot(x='Cache Size', y='Total Energy', data=dataq3, hue="Loop Unroll Factor", edgecolor="black", ci=None)
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter("%dmW"))
    plt.title("Top Energy Usage")
    fig.legend(loc=(1.02, 0.6), title="Loop Unroll Factors")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top Total Energy Usage.png", format='png', dpi=600)
    
def q4_plots():
    dataq4 = df[(df["Accelerator"] == "top") & (df["Model"] == "Cache")]
    dataq4["Total Energy"] = dataq4["Energy"] * dataq4["Runtime Cycles"]
    dataq4 = dataq4[(dataq4["Cache Size"] == "1024K") & (dataq4["Loop Unroll Factor"] == "256")]
    print("\nDataQ4:\n")
    print(dataq4)
    #Runtime
    plt.figure()
    fig = sea.scatterplot(x='Cache Size', y='Runtime Cycles', data=dataq4, hue="Optimized", edgecolor="black", ci=None)
    plt.title("Top: Optimized vs Unoptimized Runtime")
    fig.legend(loc=(1.02, 0.6), title="Optimized")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top: Optimized vs Unoptimized Cache Accesses.png", format='png', dpi=600)
    
    #Energy
    plt.figure()
    fig = sea.scatterplot(x='Cache Size', y='Total Energy', data=dataq4, hue="Optimized", edgecolor="black", ci=None)
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter("%dmW"))
    plt.title("Top: Optimized vs Unoptimized Total Energy")
    fig.legend(loc=(1.02, 0.6), title="Optimized")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top: Optimized vs Unoptimized Total Energy.png", format='png', dpi=600)

def q5_plots():
    dataq1 = df[(df["Accelerator"] == "top") & (df["Optimized"] == "Unoptimized") & (df["Model"] == "DMA_Tile")]
    dataq1["Multipliers"] = dataq1["Loop Unroll Factor"]
    print("\nDataQ5:\n")
    print(dataq1)
    plt.figure()
    fig = sea.scatterplot(x='Multipliers', y='Runtime Cycles', hue="Multipliers", data=dataq1, edgecolor="black", ci=None)
    plt.title("Top Runtime Performance DMA_Tile")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top Runtime Performance DMA_Tile.png", format='png', dpi=600)

def q6_plots():
    dataq2 = df[(df["Accelerator"] == "top") & (df["Optimized"] == "Unoptimized") & (df["Model"] == "DMA_Tile")]
    dataq2["Total Energy"] = dataq2["Energy"] * dataq2["Runtime Cycles"]
    dataq2["Multipliers"] = dataq2["Loop Unroll Factor"]
    print("\nDataQ6:\n")
    print(dataq2)
    plt.figure()
    fig = sea.scatterplot(x='Multipliers', y='Total Energy', data=dataq2, hue="Multipliers", edgecolor="black", ci=None)
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter("%dmW"))
    plt.title("Top: Energy Usage DMA_Tile")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top: Energy Usage DMA_Tile.png", format='png', dpi=600)
    
def q7_plots():
    dataq1 = df[(df["Accelerator"] == "top") & (df["Optimized"] == "Unoptimized") & (df["Model"] == "DMA_Tile_Merged")]
    dataq1["Multipliers"] = dataq1["Loop Unroll Factor"]
    print("\nDataQ7:\n")
    print(dataq1)
    plt.figure()
    fig = sea.scatterplot(x='Multipliers', y='Runtime Cycles', data=dataq1, hue="Multipliers", edgecolor="black", ci=None)
    plt.title("Top Runtime Performance DMA_Tile_Merged")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top Runtime Performance DMA_Tile_Merged.png", format='png', dpi=600)

def q8_plots():
    dataq2 = df[(df["Accelerator"] == "top") & (df["Optimized"] == "Unoptimized") & (df["Model"] == "DMA_Tile_Merged")]
    dataq2["Total Energy"] = dataq2["Energy"] * dataq2["Runtime Cycles"]
    dataq2["Multipliers"] = dataq2["Loop Unroll Factor"]
    print("\nDataQ8:\n")
    print(dataq2)
    plt.figure()
    fig = sea.scatterplot(x='Multipliers', y='Total Energy', data=dataq2, hue="Multipliers", edgecolor="black", ci=None)
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter("%dmW"))
    plt.title("Top: Energy Usage DMA_Tile_Merged")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("Top: Energy Usage DMA_Tile_Merged.png", format='png', dpi=600)

def doplot_benchmarks(benchmarks,stat,norm=True):
    performance_plots()

rows = []
for i,ac in enumerate(accelerators):
    for j,im in enumerate(image_sizes):
        for k,bm in enumerate(benchmarks):
            for l,ci in enumerate(images):
                rows.append(["Cache",ac,im,getCSstat(datadir, im+"_"+ac+"_"+ci+".txt", ac,  "Performance"),getCSstat(datadir, im+"_"+ac+"_"+ci+".txt", ac, "Stall_Cycles"),getCSstat(datadir, im+"_"+ac+"_"+ci+".txt", ac, "Energy")])

df = pd.DataFrame(rows, columns=["Model", "Algorithm", "Image Size", 'Runtime Cycles', "Stall Cycles", "Energy"])

df = df.replace("pl", "Push Relabel")
df = df.replace("ek", "Edmonds Karp")
print(df)

doplot_benchmarks(benchmarks,"ipc",norm=False)


