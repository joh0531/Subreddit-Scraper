#!/usr/bin/env python3

#re = open("allsubreddits.txt","w+")
wr = open("big_subreds.txt", "w")
count = 0
with open("all_big_subreds.txt","r") as re:
    for line in re:
        print('{}\n'.format(count))
        #print(line)
        l = line.split("/")
        #print(l)
        wr.write(l[-1])
        #wr.write("\n")
        count+=1
    
