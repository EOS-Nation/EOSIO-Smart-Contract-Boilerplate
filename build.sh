#!/usr/bin/env bash

cd src
eosio-cpp boilerplate.cpp -o ../boilerplate.wasm -abigen -I ../include -I ./ -R ../resources
