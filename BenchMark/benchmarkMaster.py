import os
import re

paths = []
paths.append("Literature_Instances/hb/bcspwr01.mtx.rnd")
# paths["Literature_Instances/Grid_Graphs/mesh9_9.txt"] = 36


def benchGrasp():

    grasp_command =  "g++ -g -std=c++11 -o Grasp_Benchmark graspBenchmark.cpp "
    grasp_command += "../AntiBandwidth/AntiBandwidth.cpp ../GraphGenerator/GraphGenerator.cpp ../GRASP/Grasp.cpp"

    os.system(grasp_command)

    for path in paths:

        instance_path = "../" + path
        instance_name_regex = re.compile("\/(\w+)\.")
        instance_name = instance_name_regex.search(path)
        instance_name = instance_name.group(1)

        grasp_command = "./Grasp_Benchmark " + instance_path + " " + instance_name

        if (os.system(grasp_command) != 0):
            print("Error trying to test " + instance_path )


benchGrasp()
