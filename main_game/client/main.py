import requests

import sys

if __name__ == "__main__":
    if len(sys.argv) == 3:

        r = requests.post("http://localhost:18080/submit_score",
                          json={'username': f'{sys.argv[1]}', 'score': f'{sys.argv[2]}'})
        # print(r.content) можно узнать уникальный номер и место

        jstr = requests.get("http://localhost:18080/leaderboard_top").content
        print(jstr.decode())
    else:
        print("Wrong!")
