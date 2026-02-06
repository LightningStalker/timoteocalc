#!/bin/bash
# converts fahrenheits to celsiuss
bc <<< "scale = 2; ($1 - 32) / 1.8"