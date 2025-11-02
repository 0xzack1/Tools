#!/usr/bin/env python3

"""
Subdomain Enumeration Tool for Red Team Reconnaissance

- T1590.001: Gather Victim Network Information - Domain Properties
- T1592.002: Gather Victim Host Information - Software

Performs DNS brute-force enumeration to discover subdomains of target domains.
"""

# Todo:
# 	Proper exception handling
# 	Add progress indicator
#	Validate at argparse level
#	Add file output 
#	Add Vhost mode
#	Thread pool
#	Add wildcard detection
#	Add --dns / --nameservers option to specify DNS servers for enumeration
#	Verify HTTP service

import argparse
import dns.resolver
import ipaddress
import os
import socket
import sys
from urllib.parse import urlparse

TIMEOUT = 5

def validate_url(url :str) -> tuple[bool, str]:
	try:
		parsed = urlparse(url)
		if parsed.scheme not in ('http', 'https'):
			return (False, "")
		if not parsed.hostname:
			return (False, "")

		hostname = parsed.hostname

		try:
			ipaddress.ip_address(hostname)
			return (True, hostname)
		except ValueError:
			pass

		try:
			is_valid = len(socket.getaddrinfo(hostname, None)) > 0
			return (is_valid, hostname if is_valid else "")
		except socket.gaierror:
			return (False, "")
		except Exception:
			return (False, "")
	except Exception:
		return (False, "")

def enumerate_subdomains(domain, wordlist):
	resolver = dns.resolver.Resolver()
	resolver.timeout = TIMEOUT
	resolver.lifetime = TIMEOUT
	record_types = ['A','AAAA', 'CNAME']
	results = []

	with open(wordlist, 'r') as f: 
		for sub in f.read().splitlines():
			full_domain = f"{sub}.{domain}"
			for rtype in record_types:
				try:
					answers = resolver.resolve(full_domain, rtype)
					for rdata in answers:
						if rtype in ('A', 'AAAA'):
							results.append((full_domain, rtype, rdata.address))
						elif rtype == 'CNAME':
							results.append((full_domain, rtype, str(rdata.target)))
						else:
							results.append((full_domain, rtype, str(rdata)))
				except (dns.resolver.NXDOMAIN, dns.resolver.NoAnswer, dns.resolver.NoNameservers, dns.exception.Timeout):
					pass
	return results


def parse_args() -> argparse.Namespace:
	parser = argparse.ArgumentParser(description='Subdomain Enumeration Tool for Red Team Reconnaissance')
	parser.add_argument('url', help='Target URL (e.g., https://example.com)')
	parser.add_argument('wordlist', help='Path to subdomain wordlist file')
	return parser.parse_args()

def main():
	args = parse_args()
	url = args.url.strip()
	
	wordlist = args.wordlist
	if not os.path.isfile(wordlist):
		print("Wordlist file does not exist")
		sys.exit(1)
	
	valid, hostname = validate_url(url)
	if not valid:
		print("Invalid URL")
		sys.exit(2)
	
	results = enumerate_subdomains(hostname, wordlist)
	for domain, rtype, value in results:
		print(f"[+] {domain:<40} {rtype:<6} {value}")
		
	print(f"\n[*] Total records discovered: {len(results)}")

if __name__	== '__main__':
	main()
