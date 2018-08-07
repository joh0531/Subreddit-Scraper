#include "map.h"

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <strings.h>

void usage(int code) {
    fprintf(stderr, "Usage: ./store_reddit [Options]\n\tOptions:\n\t-n NUMBER (1-27)\n\t-s STAT (comment_count, (default) scores, title_length, subscribers)\n\t-b BACKEND (treap, (default) rbtree, bst) \n\tProgram reads subreddit names from stdin and calculates statistics on the field (STAT) on these subreddits, ordered by the mean value\n");
    exit(code);
}

int main(int argc, char * argv[]) {
    
    std::string sort_by = "scores";
    std::string backend = "rbtree";
    int sub_num = 20; 
    size_t optind;
    for (optind = 1; (int) optind < argc && argv[optind][0] == '-'; optind++) {
        switch (argv[optind][1]) {
        case 'h': usage(1); break;
        case 'n':
            optind++;
            sub_num = std::stoi(argv[optind]); 
            if (sub_num<1||sub_num>27) usage(1);
            break;
        case 's':
            optind++;
            sort_by = argv[optind];
            break;
        case 'b':
            optind++;
            backend = argv[optind];
            break;
        default:
            usage(1);
           
        
        }   
    }
    Map * map;
    if (backend.compare("rbtree") == 0){
        map = new RBTreeMap();
    } else if (backend.compare("bst") == 0) {
        map = new BSTMap();
    } else if (backend.compare("treap") == 0) {
        map = new TreapMap();
    } else {
        fprintf(stderr, "Not a valid backend\n");
        usage(1);
    }

    std::string subred;
    //execute series of commands on each subreddit.
    while(getline(std::cin, subred)){
        int count = 0;
        std::string subreds = "'" + subred + "'";
        std::string command = "./pull_reddit.py " + subreds + " " + std::to_string(sub_num);

        char buf[BUFSIZ];
        FILE * output;
        //std::cout << "grabbing output for: " << command << std::endl;
        output = popen(command.c_str(), "r");
        if (output==NULL) {
            fprintf(stderr, "Subreddit does not exist\n");
            continue;
        }
        double sum = 0;
        double max = 0;
        double min = INT_MAX;
        //calculate statistics on artcles
        while (fgets(buf, BUFSIZ, output)){
            std::string title = buf;
            *buf = 0;
            count++;
            fgets(buf, BUFSIZ, output);
            std::string subscribers = buf;
            *buf = 0;
            fgets(buf, BUFSIZ, output);
            std::string creation_time = buf;
            *buf = 0;
            fgets(buf, BUFSIZ, output);
            std::string comment_count = buf;
            *buf = 0;
            fgets(buf, BUFSIZ, output);
            std::string score = buf;
            *buf = 0;
            //std::cout << title << " " << subscribers << " " << creation_time << " " << comment_count << " " << score << std::endl;
            if (sort_by.compare("creation_time")==0){
                 double c_time = std::stod(creation_time);
                 sum+=c_time;
                 if (c_time < min) {
                     min = c_time;
                 } 
                 if (c_time > max) {
                     max = c_time;
                 }
            } else if (sort_by.compare("comment_count")==0){
                 double com_count = std::stod(comment_count);
                 sum+=com_count;
                 if (com_count < min) {
                     min = com_count;
                 }
                 if (com_count > max) {
                     max = com_count;
                 } 
            } else if (sort_by.compare("scores")==0){
                 double sc = std::stod(score);
                 sum+=sc;
                 if (sc < min) {
                     min = sc;
                 } 
                 if (sc > max) {
                     max = sc;
                 } 
            } else if (sort_by.compare("title_length")==0){
                 double ti = title.length();
                 sum+=ti;
                 if (ti < min) {
                     min = ti;
                 } 
                 if (ti > max) {
                     max = ti;
                 } 
            } else if (sort_by.compare("subscribers")==0){
                 double subs = std::stod(subscribers);
                 sum+=subs;
                 if (subs < min) {
                     min = subs;
                 } 
                 if (subs > max) {
                     max = subs;
                 } 
            } else {
                fprintf(stderr, "Incorrect sort_by argument\n");
                pclose(output);
                usage(1);
            }

        }

        if(pclose(output))  {
            printf("Command not found or exited with error status\n");
            return -1;
        }
        
        int mean, range;
        if (count == 0) {
            mean = 0;
            max = 0;
            min = 0;
            range = 0;
        } else {
            mean = (int) (sum / (double) count);
            range = (int) (max - min);
        }


        map->insert(mean, subred, count, max, min, range);
        /*
        if (stat.compare("mean")==0){
            map->insert(subred,  mean);
        } else if (stat.compare("range")==0){
            map->insert(subred, range);
        } else if (stat.compare("max")==0){
            map->insert(subred, (int) max);
        } else if (stat.compare("min")==0){
            map->insert(subred, (int) min);
        } else {
            usage(1);
        }
        */
    }

    map->dump(std::cout, DUMP_KEY_VALUE);
    delete map;
    return 0;
}
