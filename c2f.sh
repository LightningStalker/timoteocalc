#!/bin/bash
# covnert ceslius to fareinheight
bc <<< "scale = 2; $1 * 1.8 + 32"