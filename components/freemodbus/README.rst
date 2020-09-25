# Modbus assumptions, dependencies and constraints

1. The only one Modbus master and slave port can be initialized at the same time.
2. The maximum number of registers to read/write in one transaction accordingly is 125/120 registers (standard Modbus limitation).