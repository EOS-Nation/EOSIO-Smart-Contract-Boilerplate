#!/usr/bin/env bash

cd src
eosio-cpp notechain.cpp -o ../notechain.wasm -abigen -I ../include -I ./ -R ../resources
