# Simple Python code to generate HMAC test cases
#
# (Can't use the NIST vectors as each vector has a unique key)
#
import hmac, hashlib

key = b"".join(chr(x) for x in reversed([ 1,2,3,4,5,6,7,8,9,10,11,12,13,
                                 14,15,16,17,18,19,20,21,22,23,
                                 24,25,26,27,28,29,30,31,32 ]))

messages = [
    b"\x00" * 64,
    b"",
    b"Hello world",
    b"Another message goes here",
    b"\x33" * 1024,
    b"\x33" * 1024 + b"ABC",
    ]

idx = 0

def hexarray(m):
    return ", ".join("0x%02x" % ord(x) for x in m)

for m in messages:
    h = hmac.new(key, m, hashlib.sha256)
    idx += 1

    print("const uint8_t msg%d[] = { %s };" % (idx, hexarray(m)))
    print("const uint8_t mac%d[] = { %s };" % (idx, hexarray(h.digest())))
    print("")
    print("r = ets_hmac_calculate_message(key_block, msg%d, sizeof(msg%d), hmac);" % (idx, idx))
    print("TEST_ASSERT_EQUAL(0, r);")
    print("ESP_LOG_BUFFER_HEX(\"hmac\", hmac, 32);")
    print("TEST_ASSERT_EQUAL_HEX8_ARRAY(mac%d, hmac, sizeof(hmac));" % (idx,))
    print("\n")


