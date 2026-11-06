# Antivirus Industry Career & Technical Preparation Guide

---

## 🎯 Target Companies & Application Map

| Company | Key India Hub / Offices | Primary Product Focus Areas |
| :--- | :--- | :--- |
| **McAfee** | Bengaluru (Karnataka) | Consumer & Enterprise EPP, EDR, ATP, Consumer Threat Intelligence |
| **Trend Micro** | Bengaluru, Mumbai | Cloud Security, Enterprise XDR, Network & Endpoint Protection |
| **Quick Heal Technologies** | Pune (HQ), Bengaluru | Endpoint Security, Seqrite Enterprise EDR/XDR, Mobile Security |
| **Bitdefender** | Remote / Regional Sales & Tech Support | Consumer & Enterprise Endpoint, MDR, EDR |
| **ESET** | Bengaluru, Pune | Endpoint Protection, Threat Intelligence (LiveGrid), EDR |
| **Gen Digital** *(Avast, AVG, Norton, Avira)* | Bengaluru (R&D / Product Engineering) | Consumer Endpoint Security, Threat Labs, Identity Protection |
| **Kaspersky** | Remote / Regional Technical Units | Enterprise Endpoint, Industrial Cybersecurity (KICS), Threat Intelligence |

---

## 📄 Role 1: Security Researcher (EPP / ATP / Efficacy & Malware)

### Position Summary & Context
* **Target Company:** McAfee (Bangalore Development Center)
* **Work Model:** Hybrid (2–3 days on-site / week)
* **Required Experience:** 2 to 3 years in Malware Analysis, Threat Intelligence, and Endpoint Security (EPP, EDR, XDR, ATP)

---

### Core Skill Architecture & Breakdown

#### 1. Dynamic & Static Malware Analysis
* **Dynamic Behavior Monitoring:** Tracing process trees, process injections (DLL injection, Process Hollowing), persistence mechanisms (`Registry Run Keys`, `Scheduled Tasks`, `WMI Event Subscriptions`), and network/file system mutations using **Procmon**, **Process Explorer**, **Wireshark**, and **Sysmon**.
* **Command-Line & Script Deobfuscation:** Decoding heavily obfuscated PowerShell (`-Enc`, XOR, Base64 loops), VBScript, Command Prompt scripts, and macro-based Office payloads using **CyberChef** and **Regex**.
* **Static Analysis Fundamentals:** Inspecting PE headers (sections, import/export tables, compile timestamps, rich headers), entropy scoring for packed/encrypted binaries, and cryptographic/fuzzy hashing (`MD5`, `SHA256`, `ssdeep`, `imphash`).
* **Sandbox Analysis & Triage:** Interpreting execution logs, API call sequences, and behavior scores from platforms like **ANY.RUN**, **Hybrid Analysis**, **Joe Sandbox**, and **VirusTotal**.

#### 2. False Positive (FP) & Detection Gap Analysis
* **Root-Cause Investigation:** Differentiating benign administrative tooling (e.g., PSExec, administrative PowerShell scripts, IT monitoring agents) from Living-off-the-Land (LotL / LOLBins) techniques.
* **Tuning & Recommendations:** Formulating precise exclusion rules, signature updates, or behavioral rule modifications to eliminate FPs without introducing security blind spots.
* **Telemetry Parsing:** Navigating Windows Event Logs (`Event ID 4688` - Process Creation, `4624` - Successful Logon, `7045` - Service Creation) and endpoint sensor telemetry to pinpoint detection failures.

#### 3. EPP / EDR / XDR / ATP Efficacy & Test Set Curation
* **Test Set Curation:** Building and maintaining fresh, behaviorally active malware sets (ransomware, infostealers, loaders, RATs) while filtering out dead/inactive C2 samples or corrupted binaries.
* **Adversary Emulation:** Executing controlled attack techniques using **Atomic Red Team**, custom PowerShell/Python scripts, or **Caldera** to test protection and detection layers.
* **Isolated Test Lab Management:** Configuring and reverting nested virtualization lab environments (**VMware ESXi**, **Hyper-V**, **VirtualBox**) using isolated network simulation tools (**INetSim**, **FakeNet-NG**).

#### 4. Third-Party Efficacy Testing Methodologies
* **Standard Frameworks:** Understanding test methodologies enforced by evaluation bodies (**AV-Comparatives**, **AV-TEST**, **SE Labs**, **MRG Effitas**).
* **Metrics & Scoring:** Tracking Protection Rates, Detection Rates, FP Counts, Block vs. Compromise Points, and Time-to-Detect / Time-to-Protect metrics.
* **Competitive Benchmarking:** Replicating third-party evaluation workflows internally to identify product gaps prior to official public certification runs.

#### 5. MITRE ATT&CK & Automation
* **ATT&CK Mapping:** Mapping observed malware behaviors, attack vectors, and simulation artifacts to specific ATT&CK Tactics, Techniques, and Procedures (TTPs).
* **Automated Tooling:** Writing Python and PowerShell scripts to automate sample fetching via VirusTotal APIs, hash lookups, PE metadata extraction, and report generation.

---

### Recommended Portfolio Projects to Build

#### Project 1: Automated Efficacy Testing & Threat Set Curation Pipeline
* **Objective:** Build an automated pipeline to ingest, validate, curate, and test live malware samples against endpoint security rules.
* **Tech Stack:** Python, VirusTotal API v3, ANY.RUN API, Docker, Atomic Red Team, PowerShell.
* **Key Features:**
  * Automated downloading of fresh samples based on prevalence tags (e.g., `ransomware`, `stealer`).
  * De-duplication and filter validation checking C2 liveness and PE header validity.
  * Auto-execution inside a sandboxed VM with automated logging of hit/miss rates against target detection rules.
  * Dynamic generation of a Markdown execution and efficacy report.

#### Project 2: Windows Telemetry & False Positive Analyzer Tool
* **Objective:** Create a root-cause analysis utility for Windows Event Logs and Sysmon logs to triage FP triggers caused by legitimate admin activity (LOLBins).
* **Tech Stack:** Python, `python-evt`, Sysmon (Event IDs 1, 3, 7, 11, 13), Pandas, CyberChef API.
* **Key Features:**
  * Ingests EVTX files and parses process creation chains (`Event ID 4688` / Sysmon `Event ID 1`).
  * Calculates rule signal-to-noise ratio by comparing process parameters against known-good baseline hash files.
  * Outputs suggested exclusion/tuning recommendations for detection rules.

---

## 📄 Role 2: Malware Research Engineer (macOS)

### Position Summary & Context
* **Target Focus:** End-to-End macOS Threat Analysis & Detection Engineering
* **Required Experience:** 3 to 5 years in Mach-O Reverse Engineering, macOS Internals, and Signature/Rule Creation
* **Key Languages & Tools:** C, C++, Objective-C, Swift, Python, Bash/Zsh, Ghidra, IDA Pro, Hopper, LLDB

---

### Core Technical Pillars

```
                    macOS Malware Analysis Spectrum
                                │
┌───────────────────────────────┼───────────────────────────────┐
▼                               ▼                               ▼

macOS Internals & Security    Reverse Engineering & Triage    Detection & Telemetry
──────────────────────────    ────────────────────────────    ─────────────────────
• Gatekeeper & XProtect       • Mach-O Header Structure       • YARA Rule Writing
• SIP (System Integrity)      • DYLD Dynamic Linker           • Behavioral Signatures
• TCC (Privacy Permissions)   • PKG/DMG Installer Analysis    • LaunchAgent/Daemon Audit
• Notarization Bypass         • Hopper / Ghidra / LLDB        • Endpoint Security API
```

#### 1. macOS Security Architecture & Internals
* **System Controls:** In-depth understanding of **Gatekeeper**, **XProtect**, **SIP (System Integrity Protection)**, and **TCC (Transparency, Consent, and Control)** framework.
* **Mach-O Binary Internals:** Deep understanding of headers, load commands (`LC_LOAD_DYLIB`, `LC_CODE_SIGNATURE`), section layouts (`__TEXT`, `__DATA`), and `DYLD` dynamic library loading/hijacking.
* **macOS Persistence Mechanisms:** Auditing and monitoring `LaunchAgents`, `LaunchDaemons`, Login Items, Cron jobs, System Extensions, and Authorization Plugins.

#### 2. Reverse Engineering & Analysis Workflow
* **Static Analysis:** Inspecting Mach-O binaries, universal (fat) binaries, malicious `.pkg` installer scripts, `.dmg` container files, and AppleScripts using **Hopper Disassembler**, **IDA Pro**, and **Ghidra**.
* **Dynamic Analysis & Debugging:** Live process debugging, breakpoint setting, and memory inspection using **LLDB** and native tracing utilities (`dtrace`, `fs_usage`, `opensnoop`).
* **Evasion Techniques:** Tracking code signing misuse, notarization abuse, sandbox escape attempts, and zero-day exploitation methods targeting macOS core components.

#### 3. Detection Engineering & Threat Intel Output
* **YARA & Heuristic Rule Development:** Writing optimized YARA rules for Mach-O binaries and shell script payloads to minimize false positives.
* **Technical Threat Reporting:** Drafting detailed threat research blogs, whitepapers, and IOC lists mapping macOS malware families to the MITRE ATT&CK for Enterprise (macOS Matrix).

---

### Recommended Portfolio Projects to Build

#### Project 1: macOS Persistence Auditor & YARA Scanner (`mac-persist-guard`)
* **Objective:** A lightweight Swift/Python tool that audits critical macOS persistence vectors and scans active LaunchAgents/LaunchDaemons with YARA rules.
* **Tech Stack:** Swift, Python, `libyara-python`, macOS Native APIs (`NSFileManager`).
* **Key Features:**
  * Traverses system and user-level `LaunchAgents` and `LaunchDaemons` directories.
  * Extracts plist target binaries and checks code signatures (`codesign -dvvv`).
  * Runs YARA signatures across unverified Mach-O binaries and flags unsigned or suspicious executables.

#### Project 2: Mach-O Static Analysis & Metadata Parser (`macho-inspector`)
* **Objective:** A CLI utility for security researchers to analyze Mach-O binaries for suspicious characteristics.
* **Tech Stack:** Python / C++, `lief` library or native Mach-O binary parsing APIs.
* **Key Features:**
  * Parses Mach-O headers, load commands, imports/exports, and segment entropic values.
  * Detects missing hardened runtime flags, missing stack canaries, and unusual DYLD loading commands (`@executable_path`, `@rpath` hijacking vectors).
  * Outputs findings structured in JSON and Markdown formats.

---

## 💡 Resume Action Plan

```
[Study Key Topics] ──► [Build Portfolio Projects] ──► [Push Code to GitHub] ──► [Add Metrics to Resume]
```

### Resume Project Section Template


### Key Projects

#### Automated Efficacy & Malware Triage Pipeline | Python, Docker, VT API, Atomic Red Team
* Designed an automated test set curation tool ingesting 100+ daily live samples via VirusTotal API to benchmark detection efficacy.
* Implemented dynamic execution routines using Atomic Red Team scripts, measuring detection and block rates across EPP/EDR behavioral engines.
* Reduced false positive validation time by 40% through automated Windows EVTX log parsing and Sysmon telemetry correlation.

#### Mach-O Static Inspector & Persistence Scanner | Swift, Python, YARA, macOS Internals
* Developed an open-source CLI utility to parse Mach-O headers, dynamic library load commands, and code-signing entitlements.
* Built automated detection routines scanning system LaunchAgents and LaunchDaemons against custom YARA rules targeting macOS backdoors.


