#!/bin/bash
# covnert ceslius to fareinheight
# here we are born to be strings
bc <<< "scale = 2; $1 * 1.8 + 32"
