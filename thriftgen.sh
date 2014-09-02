#!/bin/bash
rm ./service/*
thrift -v -r -strict -out ./service --gen cpp:pure_enums ./thrift/chord.thrift
thrift -v -r -strict -out ./service --gen cpp:pure_enums ./thrift/datastore.thrift

