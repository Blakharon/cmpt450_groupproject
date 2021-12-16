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
accelerators = ["pl", "ek"]
acclerators_names = ["Push Relabel", "Edmonds Karp"]

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
    average_rows = []

    for imgsize in image_sizes:
        for ac in acclerators_names:
            avg = df[(df["Image Size"] == imgsize) & (df["Algorithm"] == ac)]
            average_rows.append([ac,imgsize,avg["Runtime Cycles"].mean()])
            
    df_average_rows = pd.DataFrame(average_rows, columns=["Algorithm", "Image Size", "Average Runtime Cycles"])
    
    print("Average Runtime Cycles")
    print(df_average_rows)

    plt.figure()
    fig = sea.barplot(x='Image Size', y='Average Runtime Cycles', data=df_average_rows, hue="Algorithm", edgecolor="black", ci=None)
    plt.title("MaxFlow Runtime Performance")
    fig.legend(loc=(1.02, 0.6), title="Algorithm")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("MaxFlow Runtime Performance.png", format='png', dpi=600)

def stall_cycle_plots():
    average_rows = []

    for imgsize in image_sizes:
        for ac in acclerators_names:
            avg = df[(df["Image Size"] == imgsize) & (df["Algorithm"] == ac)]
            average_rows.append([ac,imgsize,avg["Stall Cycles"].mean()])
            
    df_average_rows = pd.DataFrame(average_rows, columns=["Algorithm", "Image Size", "Average Stall Cycles"])
    
    print("Average Stall Cycles")
    print(df_average_rows)

    plt.figure()
    fig = sea.barplot(x='Image Size', y='Average Stall Cycles', data=df_average_rows, hue="Algorithm", edgecolor="black", ci=None)
    plt.title("MaxFlow Stall Cycles")
    fig.legend(loc=(1.02, 0.6), title="Algorithm")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("MaxFlow Stall Cycles.png", format='png', dpi=600)
   
def energy_plots():
    average_rows = []

    for imgsize in image_sizes:
        for ac in acclerators_names:
            avg = df[(df["Image Size"] == imgsize) & (df["Algorithm"] == ac)]
            average_rows.append([ac,imgsize,avg["Total Energy"].mean()])
            
    df_average_rows = pd.DataFrame(average_rows, columns=["Algorithm", "Image Size", "Average Total Energy"])
    
    print("Average Total Energy")
    print(df_average_rows)

    plt.figure()
    fig = sea.barplot(x='Image Size', y='Average Total Energy', data=df_average_rows, hue="Algorithm", edgecolor="black", ci=None)
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter("%dmW"))
    plt.title("MaxFlow Energy Usage")
    fig.legend(loc=(1.02, 0.6), title="Algorithm")
    plt.tight_layout()
    plt.autoscale(enable=True, axis='x', tight=False)
    plt.savefig("MaxFlow Energy Usage.png", format='png', dpi=600)

def doplot_benchmarks(benchmarks,stat,norm=True):
    performance_plots()
    stall_cycle_plots()
    energy_plots()

rows = []
for i,ac in enumerate(accelerators):
    for j,im in enumerate(image_sizes):
        for l,ci in enumerate(images):
            rows.append(["Cache",ac,im,getCSstat(datadir, im+"_"+ac+"_"+ci+".txt", ac,  "Performance"),getCSstat(datadir, im+"_"+ac+"_"+ci+".txt", ac, "Stall_Cycles"),getCSstat(datadir, im+"_"+ac+"_"+ci+".txt", ac, "Energy")])

df = pd.DataFrame(rows, columns=["Model", "Algorithm", "Image Size", 'Runtime Cycles', "Stall Cycles", "Energy"])

df = df.replace("pl", "Push Relabel")
df = df.replace("ek", "Edmonds Karp")

df["Total Energy"] = df["Energy"] * df["Runtime Cycles"]
print(df)

doplot_benchmarks(benchmarks,"ipc",norm=False)


