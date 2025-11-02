# Subdomain Enumeration Tool for Red Team Reconnaissance

A lightweight Python DNS brute-force subdomain enumeration tool designed for red team reconnaissance operations and penetration testing.

## MITRE ATT&CK Mapping

- **T1590.001**: Gather Victim Network Information - Domain Properties
- **T1592.002**: Gather Victim Host Information - Software

## Features

- Brute‑forces subdomains from a wordlist (one subdomain per line)
- URL validation with hostname extraction
- Queries A, AAAA, and CNAME DNS records
- Lightweight with minimal dependencies (dnspython)

## Usage

```bash
python3 subdomain_enum.py <url> <wordlist>
```

- ```<url>```: Target URL (e.g., ```https://example.com```)
- ```<wordlist>```: Path to subdomain wordlist file

**Example**:

```bash
└─$ python3 subdomain_enum.py https://google.com wordlist.txt 

[+] www.google.com                           A      142.251.29.105
[+] www.google.com                           A      142.251.29.99
[+] www.google.com                           A      142.251.29.103
[+] www.google.com                           A      142.251.29.106
[+] www.google.com                           A      142.251.29.147
[+] www.google.com                           A      142.251.29.104
[+] www.google.com                           AAAA   2a00:1450:4009:c04::69
[+] www.google.com                           AAAA   2a00:1450:4009:c04::6a
[+] www.google.com                           AAAA   2a00:1450:4009:c04::68
[+] www.google.com                           AAAA   2a00:1450:4009:c04::63
[+] code.google.com                          A      142.251.30.102
[+] code.google.com                          A      142.251.30.139
[+] code.google.com                          A      142.251.30.101
[+] code.google.com                          A      142.251.30.113
[+] code.google.com                          A      142.251.30.138
[+] code.google.com                          A      142.251.30.100
[+] code.google.com                          AAAA   2a00:1450:4009:c15::8a
[+] code.google.com                          AAAA   2a00:1450:4009:c15::65
[+] code.google.com                          AAAA   2a00:1450:4009:c15::66
[+] code.google.com                          AAAA   2a00:1450:4009:c15::8b
[+] code.google.com                          CNAME  code.l.google.com.
[+] chrome.google.com                        A      142.250.129.139
[+] chrome.google.com                        A      142.250.129.100
[+] chrome.google.com                        A      142.250.129.101
[+] chrome.google.com                        A      142.250.129.138
[+] chrome.google.com                        A      142.250.129.102
[+] chrome.google.com                        A      142.250.129.113
[+] chrome.google.com                        AAAA   2a00:1450:4009:c04::71
[+] chrome.google.com                        AAAA   2a00:1450:4009:c04::8a
[+] chrome.google.com                        AAAA   2a00:1450:4009:c04::66
[+] chrome.google.com                        AAAA   2a00:1450:4009:c04::8b
[+] chrome.google.com                        CNAME  www3.l.google.com.
[+] analytics.google.com                     A      142.250.151.101
[+] analytics.google.com                     A      142.250.151.102
[+] analytics.google.com                     A      142.250.151.139
[+] analytics.google.com                     A      142.250.151.138
[+] analytics.google.com                     A      142.250.151.113
[+] analytics.google.com                     A      142.250.151.100
[+] analytics.google.com                     AAAA   2001:4860:4802:38::181
[+] analytics.google.com                     AAAA   2001:4860:4802:36::181
[+] analytics.google.com                     AAAA   2001:4860:4802:34::181
[+] analytics.google.com                     AAAA   2001:4860:4802:32::181
[+] analytics.google.com                     CNAME  analytics-alv.google.com.
[+] docs.google.com                          A      142.250.117.100
[+] docs.google.com                          A      142.250.117.139
[+] docs.google.com                          A      142.250.117.138
[+] docs.google.com                          A      142.250.117.102
[+] docs.google.com                          A      142.250.117.101
[+] docs.google.com                          A      142.250.117.113
[+] docs.google.com                          AAAA   2a00:1450:4009:c0b::71
[+] docs.google.com                          AAAA   2a00:1450:4009:c0b::8a
[+] docs.google.com                          AAAA   2a00:1450:4009:c0b::66
[+] docs.google.com                          AAAA   2a00:1450:4009:c0b::65

[*] Total records discovered: 53

```
## Roadmap

- [ ] Custom DNS server specification
- [ ] Virtual host (vhost) enumeration mode for web application testing
- [ ] Multi-threading support for faster enumeration
- [ ] JSON/CSV output formats for integration with reporting tools
- [ ] Wildcard DNS detection and filtering
- [ ] Progress indicators for large wordlists
- [ ] Improved exception handling with verbose mode
- [ ] Argparse-level file validation


