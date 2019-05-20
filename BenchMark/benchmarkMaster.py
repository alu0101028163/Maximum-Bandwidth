import os
import re

paths = {}
paths["Literature_Instances/hb/bcspwr01.mtx.rnd"] = 17
paths["Literature_Instances/Grid_Graphs/mesh9_9.txt"] = 36


def benchGrasp():
    for key in paths:
        # grasp_command =  "g++ -g -std=c++11 -o Grasp_Benchmark graspBenchmark.cpp "
        # grasp_command += "../AntiBandwidth/AntiBandwidth.cpp ../GraphGenerator/GraphGenerator.cpp ../GRASP/Grasp.cpp"

        instance_path = key
        instance_name_regex = re.compile("\/(\w+)\.")
        instance_name = instance_name_regex.search(key)
        instance_name = instance_name.group(1)
        instance_value = paths[key]

        print("Instance path  " + instance_path)
        print("Instance name  " + instance_name)
        print("Instance value " + str(instance_value))

        # os.system(grasp_command)

benchGrasp()
