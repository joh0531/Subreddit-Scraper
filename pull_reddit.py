#!/usr/bin/env python3
import requests
import os
import sys

def multireddit(subreddits, limit=20, orderby='score'):
    ''' Displays an HTML listing of the top `limit` articles from the
    various `subreddits` specified by the user.  These articles will be
    sorted by the field specified by `orderby`

      - `subreddits` is a comma-separated list of subreddits (ie.
        `linux,linuxmasterrace`)

      - `orderby` is any field in the Reddit JSON data for a particular
        article (ie. `score`, `title`, `created_utc`, etc.)
    '''
    
    if not subreddits:
        return

    
    queries = subreddits.split(",")
    
    # TODO: Process function arguments
    params   = {'action': 'subreddits', 'list': 'search', 'format': 'json', 'srsearch': subreddits}
    headers  = {'user-agent': 'reddit-{}'.format(os.environ['USER'])}
    
    results = []
    for query in queries:
        URL="https://www.reddit.com/r/"+query+"/.json"
        response = requests.get(URL, headers=headers, params=params)
        count = 0
        
        while response.status_code != 200 and count < 30:
            response = requests.get(URL, headers=headers, params=params)
            count+=1
            
        if count == 30 and response.status_code != 200:
            print('Unable to retrieve search for {}: {}'.format(subreddits, response.text))
            return
        
        data = response.json()
        
        for article in data['data']['children']:
            results.append(article['data'])
            
    counter = 0

    #//f = open("data.txt", "w+")

    for article in sorted(results, key=lambda a: a[orderby], reverse = True)[:limit]:
        counter += 1
        print("{}\n{}\n{}\n{}\n{}".format(article['title'], article['subreddit_subscribers'], article['created_utc'], article['num_comments'], article['score']))
#"https://www.reddit.com" + article['permalink'])
        #f.write(print_string)
    
    #f.close()


multireddit(sys.argv[1], int(sys.argv[2]))
