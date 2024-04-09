# NYU ProcDesign Development Template

A template for doing SystemVerilog development for the NYU Processor Design
team.

## What is a registery? 
### A registry is a collection of information about packages

## What is a package?
### A package is a collection of files and libraries required by different software programs

## What’s the difference between an interface library and a “normal” library or executable?
An interface library can consist of code and files that aren’t compiled immediately, however in normal libraries all the code and files are compiled immediately. These come useful when you need to dynamically generate code based on templates, which may require additional integration steps. 

## What is a top module?
Top module refers to the root module that contains all other modules; it is the highest-level module within a design hierarchy

