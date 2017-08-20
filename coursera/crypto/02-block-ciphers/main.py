from Crypto.Cipher import AES
from codecs import decode, encode
import logging

def bytes_xor(left, right):
    return bytes([l ^ r for (l, r) in zip(left, right)])

def cbc_decrypt(str_key, str_cipher_text):
    key = decode(str_key, 'hex')
    cipher_text = decode(str_cipher_text, 'hex')
    aes = AES.new(key)
    block_size = len(key)
    logging.debug("block size: " + str(block_size));
    block_count = len(cipher_text) // block_size
    logging.debug("total blocks: " + str(block_count));
    IV_cipher = cipher_text[:block_size]
    priv_cipher_block = IV_cipher
    text_blocks = []
    for i in range(1, block_count):
        start = i * block_size
        end = start + block_size
        logging.debug("reading bytes " + str(start) + " through " + str(end));
        block = cipher_text[start:end]
        text_blocks.append(bytes_xor(aes.decrypt(block), priv_cipher_block))
        priv_cipher_block = block
    last_text_block = text_blocks[-1]
    padding_size = last_text_block[-1]
    logging.debug("padding size: " + str(padding_size));
    last_end = block_size - padding_size
    text_blocks[-1] = last_text_block[:last_end]
    return "".join([text.decode("utf-8") for text in text_blocks])

def ctr_decrypt(str_key, str_cipher_text):
    key = decode(str_key, 'hex')
    cipher_text = decode(str_cipher_text, 'hex')
    aes = AES.new(key)
    block_size = 16
    logging.debug("block size: " + str(block_size));
    total_len = len(cipher_text)
    logging.debug("cipher text size: " + str(total_len));
    nonce = cipher_text[:8]
    counter = cipher_text[8:16]
    pos = block_size
    text_blocks = []
    i = 0
    while pos < total_len:
        start = pos
        end = min(start + block_size, total_len)
        size = end - start # can differ from block size
        logging.debug("reading bytes " + str(start) + " through " + str(end));
        block = cipher_text[start:end]
        mask = bytes(list(nonce) + list(counter[:7]) + [counter[7] + i])
        logging.debug("mask:" + encode(mask, 'hex').decode('utf8'))
        code = aes.encrypt(mask)
        logging.debug("code:" + encode(code, 'hex').decode('utf8'))
        text_blocks.append(bytes_xor(aes.encrypt(mask)[:size], block))
        pos = end
        i += 1
    return "".join([text.decode("utf-8") for text in text_blocks])

# logging.basicConfig(level=logging.DEBUG)

print(cbc_decrypt('140b41b22a29beb4061bda66b6747e14', '4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81'))
print(cbc_decrypt('140b41b22a29beb4061bda66b6747e14', '5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253'));

print(ctr_decrypt('36f18357be4dbd77f050515c73fcf9f2', '69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329'));
print(ctr_decrypt('36f18357be4dbd77f050515c73fcf9f2', '770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451'));

