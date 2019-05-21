import os
import re
import pandas as pd

paths = []
paths.append("Literature_Instances/hb/bcspwr01.mtx.rnd")
paths.append("Literature_Instances/hb/bcspwr02.mtx.rnd")
paths.append("Literature_Instances/hb/ash85.mtx.rnd")
paths.append("Literature_Instances/hb/ibm32.mtx.rnd")
paths.append("Literature_Instances/hb/will57.mtx.rnd")


def benchGrasp():

    grasp_command =  "g++ -g -std=c++11 -o Grasp_Benchmark graspBenchmark.cpp "
    grasp_command += "../AntiBandwidth/AntiBandwidth.cpp ../GraphGenerator/GraphGenerator.cpp ../GRASP/Grasp.cpp"

    if (os.system(grasp_command) != 0):
        print("Error trying to compile GRASP benchmark")
        quit()

    for key in paths:

        instance_path = key
        instance_name_regex = re.compile("\/(\w+)\.")
        instance_name = instance_name_regex.search(key)
        instance_name = instance_name.group(1)
        instance_value = paths[key]

        grasp_command = "./Grasp_Benchmark " + instance_path + " " + instance_name + " " + str(instance_value)

        if (os.system(grasp_command) != 0):
            print("Error trying to test " + instance_path + " during GRASP" )
            quit()



def benchTabu():

    tabu_command = "g++ -g -std=c++11 -o Tabu_Benchmark tabuBenchmark.cpp ../AntiBandwidth/catch.hpp ../GraphGenerator/GraphGenerator.cpp"
    tabu_command += " ../GRASP/Grasp.cpp ../AntiBandwidth/AntiBandwidth.cpp ../TabuSearch/TabuSearch.cpp"

    if (os.system(tabu_command) != 0):
        print("Error trying to compile TABU benchmark")
        quit()

    for filename in os.listdir("./GraspCalculations"):
        print(filename)

        df = pd.read_csv('./GraspCalculations/'+filename)
        max_label = df.loc[(df['value'] == df['value'].max())]['labeling'].unique()
        max_label = max_label[0].split(" ")

        file = open("temp_label.txt","w+")
        for i in range(len(max_label ) - 2):
            # print("Element: " + max_label[i + 1])
            file.write(max_label[i + 1] + "\n")
        file.close()

        instance_name_regex = re.compile("_(\w+)\.csv")
        instance_name = instance_name_regex.search(filename)
        instance_name = instance_name.group(1)

        print(instance_name)
        instance_path = "null"

        for path in paths:
            if instance_name in path:
                instance_path = path

        if(instance_path == "null"):
            print("Error trying to get the path for the file " + instance_name + " during tabu search")

        tabu_command = "./Tabu_Benchmark " + instance_path + " " + instance_name + " temp_label.txt"
        print(tabu_command)

        if (os.system(tabu_command) != 0):
            print("Error trying to test " + instance_name + " during TABU search")
            quit()

benchTabu()
