#!/bin/bash

# Script de pruebas rápidas para exit
# Uso: ./test_exit.sh

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

MINI="./minishell"

echo -e "${YELLOW}=== EXIT TESTS ===${NC}\n"

# Test básico
echo -e "${YELLOW}Test 1: exit 42${NC}"
echo "exit 42" | $MINI > /dev/null 2>&1
result=$?
if [ $result -eq 42 ]; then
    echo -e "${GREEN}✓ PASS${NC} (exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected 42, got $result)\n"
fi

# Test con 0
echo -e "${YELLOW}Test 2: exit 0${NC}"
echo "exit 0" | $MINI > /dev/null 2>&1
result=$?
if [ $result -eq 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected 0, got $result)\n"
fi

# Test con 255
echo -e "${YELLOW}Test 3: exit 255${NC}"
echo "exit 255" | $MINI > /dev/null 2>&1
result=$?
if [ $result -eq 255 ]; then
    echo -e "${GREEN}✓ PASS${NC} (exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected 255, got $result)\n"
fi

# Test con 256 (overflow)
echo -e "${YELLOW}Test 4: exit 256 (should be 0)${NC}"
echo "exit 256" | $MINI > /dev/null 2>&1
result=$?
if [ $result -eq 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected 0, got $result)\n"
fi

# Test con -1
echo -e "${YELLOW}Test 5: exit -1 (should be 255)${NC}"
echo "exit -1" | $MINI > /dev/null 2>&1
result=$?
if [ $result -eq 255 ]; then
    echo -e "${GREEN}✓ PASS${NC} (exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected 255, got $result)\n"
fi

# Test sin argumentos (hereda último comando)
echo -e "${YELLOW}Test 6: exit (no args, after ls)${NC}"
echo -e "ls > /dev/null\nexit" | $MINI > /dev/null 2>&1
result=$?
if [ $result -eq 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected 0, got $result)\n"
fi

# Test con argumento inválido
echo -e "${YELLOW}Test 7: exit hello (invalid arg)${NC}"
output=$(echo "exit hello" | $MINI 2>&1)
result=$?
if echo "$output" | grep -q "numeric argument required" && [ $result -eq 2 ]; then
    echo -e "${GREEN}✓ PASS${NC} (error message shown, exit code: $result)\n"
else
    echo -e "${RED}✗ FAIL${NC} (expected error and exit code 2, got $result)\n"
fi

# Test con múltiples argumentos
echo -e "${YELLOW}Test 8: exit 1 2 (too many args)${NC}"
output=$(echo -e "exit 1 2\necho still_here" | $MINI 2>&1)
if echo "$output" | grep -q "too many arguments"; then
    echo -e "${GREEN}✓ PASS${NC} (error shown, shell continues)\n"
else
    echo -e "${RED}✗ FAIL${NC} (should show 'too many arguments')\n"
fi

echo -e "${YELLOW}=== MANUAL TESTS ===${NC}"
echo "Try these manually:"
echo "1. echo hello | exit   (should NOT exit shell)"
echo "2. exit 300            (should exit with 44)"
echo "3. exit                (check it uses last command status)"