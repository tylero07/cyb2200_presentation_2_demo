# CYB2200 Coccinelle Presentation

**By Joe, Chris, and Tyler**

## Overview
This project is a short introduction to **Coccinelle**, a tool used for matching and transforming patterns in **C code**. For this presentation, we are focusing on a very small and simple use case so the basic idea is easier to understand.

This does **not** represent the full set of features or real-world use cases of Coccinelle. Instead, this is a short explanation and demonstration of how Coccinelle can use **pattern matching** to find and update repeated forms in C source files.

## What Coccinelle Does
Coccinelle is a tool for working with C code using rules written in **SmPL** (Semantic Patch Language). These rules can be used to:

- find repeated code patterns
- check for specific code forms
- automatically transform matching code

In basic terms, Coccinelle acts like a code-aware search-and-rewrite tool for C.

## Installation
A simple way to install Coccinelle on Ubuntu or WSL is:

```bash
sudo apt update
sudo apt install coccinelle
