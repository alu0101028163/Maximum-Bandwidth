import os
import re
import pandas as pd
import shutil

paths = []
# paths.append("../Literature_Instances/hb/ibm32.mtx.rnd") # 32 -> BASI
paths.append("../Literature_Instances/hb/bcspwr01.mtx.rnd") # 39 -> YO
# paths.append("../Literature_Instances/hb/bcspwr02.mtx.rnd") # 49 -> BASI
# paths.append("../Literature_Instances/hb/will57.mtx.rnd") # 57 -> YO
# paths.append("../Literature_Instances/hb/ash85.mtx.rnd") # 85


def securityCopy(src,dest):
    # SECURITY COPY --> ADAPT PATHS TO EACH PERSON'S COMPUTER
    src_files = os.listdir(src)
    for file_name in src_files:
        full_file_name = os.path.join(src, file_name)
        if (os.path.isfile(full_file_name)):
            shutil.copy(full_file_name, dest)

def benchGrasp():

    grasp_command =  "g++ -g -std=c++11 -o Grasp_Benchmark graspBenchmark.cpp "
    grasp_command += "../AntiBandwidth/AntiBandwidth.cpp ../GraphGenerator/GraphGenerator.cpp ../GRASP/Grasp.cpp"

    if (os.system(grasp_command) != 0):
        print("Error trying to compile GRASP benchmark")
        quit()

    for path in paths:

        instance_path = path
        instance_name_regex = re.compile("\/(\w+)\.")
        instance_name = instance_name_regex.search(path)
        instance_name = instance_name.group(1)

        if ("graspCalculations_" + instance_name + ".csv") not in os.listdir("./GraspCalculations"):

            grasp_command = "./Grasp_Benchmark " + instance_path + " " + instance_name

            if (os.system(grasp_command) != 0):
                print("Error trying to test " + instance_path + " during GRASP" )
                quit()

            src = "/home/hyydra/Documents/UNIVERSITY/DYADA/max-bandwidth/Maximum-Bandwidth/BenchMark/GraspCalculations"
            dest = "/home/hyydra/Desktop/GraspCalculations"
            securityCopy(src,dest)
        else:
            print("GRASP benchmark for file :" + instance_name + " already exists!")

def benchTabu():

    tabu_command = "g++ -g -std=c++11 -o Tabu_Benchmark tabuBenchmark.cpp ../AntiBandwidth/catch.hpp ../GraphGenerator/GraphGenerator.cpp"
    tabu_command += " ../GRASP/Grasp.cpp ../AntiBandwidth/AntiBandwidth.cpp ../TabuSearch/TabuSearch.cpp ../MatrixGenerator/Matrix_generator.cpp"

    if (os.system(tabu_command) != 0):
        print("Error trying to compile TABU benchmark")
        quit()

    for filename in os.listdir("./GraspCalculations"):
        # print(filename)

        df = pd.read_csv('./GraspCalculations/'+filename)
        max_label = df.loc[(df['value'] == df['value'].max())]['labeling'].unique()
        max_label = max_label[0].split(" ")

        file = open("temp_label.txt","w+")
        for i in range(len(max_label ) - 2):
            file.write(max_label[i + 1] + "\n")
        file.close()

        instance_name_regex = re.compile("_(\w+)\.csv")
        instance_name = instance_name_regex.search(filename)
        instance_name = instance_name.group(1)

        instance_path = "null"

        for path in paths:
            if instance_name in path:
                instance_path = path

        if(instance_path == "null"):
            print("Error trying to get the path for the file " + instance_name + " during tabu search")

        print(instance_path)
        tabu_command = "./Tabu_Benchmark " + instance_path + " " + instance_name + " temp_label.txt"

        if ("tabuCalculations_" + instance_name + ".csv") not in os.listdir("./TabuCalculations"):
            if (os.system(tabu_command) != 0):
                print("Error trying to test " + instance_name + " during TABU search")
                quit()
            src = "/home/hyydra/Documents/UNIVERSITY/DYADA/max-bandwidth/Maximum-Bandwidth/BenchMark/TabuCalculations"
            dest = "/home/hyydra/Desktop/TabuCalculations"
            securityCopy(src,dest)
        else:
            print("TABU benchmark for file: " + instance_name + " already exists!")


def benchVnd():

    vnd_command = "g++ -g -std=c++11 -o Vnd_Benchmark vndBenchmark.cpp ../AntiBandwidth/catch.hpp ../GraphGenerator/GraphGenerator.cpp"
    vnd_command += " ../GRASP/Grasp.cpp ../AntiBandwidth/AntiBandwidth.cpp ../VNS/VNS/vns.cpp ../MatrixGenerator/Matrix_generator.cpp ../NeighborhoodStructs/neighborhood.cpp"

    if (os.system(vnd_command) != 0):
        print("Error trying to compile TABU benchmark")
        quit()

    for filename in os.listdir("./GraspCalculations"):
        # print(filename)

        df = pd.read_csv('./GraspCalculations/'+filename)
        max_label = df.loc[(df['value'] == df['value'].max())]['labeling'].unique()
        max_label = max_label[0].split(" ")

        file = open("temp_label.txt","w+")
        for i in range(len(max_label ) - 2):
            file.write(max_label[i + 1] + "\n")
        file.close()

        instance_name_regex = re.compile("_(\w+)\.csv")
        instance_name = instance_name_regex.search(filename)
        instance_name = instance_name.group(1)

        instance_path = "null"

        for path in paths:
            if instance_name in path:
                instance_path = path

        if(instance_path == "null"):
            print("Error trying to get the path for the file " + instance_name + " during VND search")

        vnd_command = "./Vnd_Benchmark " + instance_path + " " + instance_name + " temp_label.txt"

        if ("VndCalculations_" + instance_name + ".csv") not in os.listdir("./VndCalculations"):
            if (os.system(vnd_command) != 0):
                print("Error trying to test " + instance_name + " during VND search")
                quit()
            src = "/home/hyydra/Documents/UNIVERSITY/DYADA/max-bandwidth/Maximum-Bandwidth/BenchMark/VndCalculations"
            dest = "/home/hyydra/Desktop/VndCalculations"
            securityCopy(src,dest)
        else:
            print("VND benchmark for file: " + instance_name + " already exists!")


def benchGvns():

    gvns_command = "g++ -g -std=c++11 -o Gvns_Benchmark gvnsBenchmark.cpp ../AntiBandwidth/catch.hpp ../GraphGenerator/GraphGenerator.cpp"
    gvns_command += " ../GRASP/Grasp.cpp ../AntiBandwidth/AntiBandwidth.cpp ../VNS/VNS/vns.cpp ../MatrixGenerator/Matrix_generator.cpp ../NeighborhoodStructs/neighborhood.cpp"

    if (os.system(gvns_command) != 0):
        print("Error trying to compile TABU benchmark")
        quit()

    for filename in os.listdir("./GraspCalculations"):
        # print(filename)

        df = pd.read_csv('./GraspCalculations/'+filename)
        max_label = df.loc[(df['value'] == df['value'].max())]['labeling'].unique()
        max_label = max_label[0].split(" ")

        file = open("temp_label.txt","w+")
        for i in range(len(max_label ) - 2):
            file.write(max_label[i + 1] + "\n")
        file.close()

        instance_name_regex = re.compile("_(\w+)\.csv")
        instance_name = instance_name_regex.search(filename)
        instance_name = instance_name.group(1)

        instance_path = "null"

        for path in paths:
            if instance_name in path:
                instance_path = path

        if(instance_path == "null"):
            print("Error trying to get the path for the file " + instance_name + " during GVNS search")

        gvns_command = "./Gvns_Benchmark " + instance_path + " " + instance_name + " temp_label.txt"

        if ("GvnsCalculations_" + instance_name + ".csv") not in os.listdir("./GvnsCalculations"):
            if (os.system(gvns_command) != 0):
                print("Error trying to test " + instance_name + " during GVNS search")
                quit()
            src = "/home/hyydra/Documents/UNIVERSITY/DYADA/max-bandwidth/Maximum-Bandwidth/BenchMark/GvnsCalculations"
            dest = "/home/hyydra/Desktop/GvnsCalculations"
            securityCopy(src,dest)
        else:
            print("GVNS benchmark for file: " + instance_name + " already exists!")


def benchMultiStart():

    multiStart_command = "g++ -g -std=c++11 -o MultiStart_Benchmark multiStartBenchmark.cpp ../AntiBandwidth/catch.hpp ../GraphGenerator/GraphGenerator.cpp"
    multiStart_command += " ../GRASP/Grasp.cpp ../AntiBandwidth/AntiBandwidth.cpp ../MultiStart/MultiStart.cpp ../MatrixGenerator/Matrix_generator.cpp ../NeighborhoodStructs/neighborhood.cpp"

    if (os.system(multiStart_command) != 0):
        print("Error trying to compile TABU benchmark")
        quit()

    for filename in os.listdir("./GraspCalculations"):
        # print(filename)

        df = pd.read_csv('./GraspCalculations/'+filename)
        max_label = df.loc[(df['value'] == df['value'].max())]['labeling'].unique()
        max_label = max_label[0].split(" ")

        file = open("temp_label.txt","w+")
        for i in range(len(max_label ) - 2):
            file.write(max_label[i + 1] + "\n")
        file.close()

        instance_name_regex = re.compile("_(\w+)\.csv")
        instance_name = instance_name_regex.search(filename)
        instance_name = instance_name.group(1)

        instance_path = "null"

        for path in paths:
            if instance_name in path:
                instance_path = path

        if(instance_path == "null"):
            print("Error trying to get the path for the file " + instance_name + " during MULTISTART search")

        multiStart_command = "./MultiStart_Benchmark " + instance_path + " " + instance_name

        if ("multiStartCalculations_" + instance_name + ".csv") not in os.listdir("./MultiStartCalculations"):
            if (os.system(multiStart_command) != 0):
                print("Error trying to test " + instance_name + " during MULTISTART search")
                quit()
            src = "/home/hyydra/Documents/UNIVERSITY/DYADA/max-bandwidth/Maximum-Bandwidth/BenchMark/MultiStartCalculations"
            dest = "/home/hyydra/Desktop/MultiStartCalculations"
            securityCopy(src,dest)
        else:
            print("MULTISTART benchmark for file: " + instance_name + " already exists!")

benchGrasp()
print("BENCHING GRASP")
benchTabu()
print("BENCHING TABU")
benchMultiStart()
print("BENCHING MULTISTART")
benchVnd()
print("BENCHING VND")
benchGvns()
print("BENCHINIG GVNS")
