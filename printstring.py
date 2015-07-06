#!/usr/bin/python
import urllib
import re
print urllib.unquote("%5B%7B%22")
print urllib.unquote("[truncated] text=test%20for%20priva%20%E5%BE%AE%E5%8D%9A%EF%BC%8C%E6%B5%8B%E8%AF%95%E2%80%9C%E4%BB%85%E8%87%AA%E5%B7%B1%E5%8F%AF%E8%A7%81%E5%BE%AE%E5%8D%9A%E2%80%9D%2C%E4%B8%80%E5%BC%A0%E5%9B%BE%E7%89%87%EF%BC%8C%E4%B8%80%E4%B8%AA%E8%A1%A8")
print urllib.unquote("[truncated] text=test%20for%20%5B%E5%98%BB%E5%98%BB%5D%20private%20%E5%BE%AE%E5%8D%9A%EF%BC%8C%E6%B5%8B%E8%AF%95%E2%80%9C%E4%BB%85%E8%87%AA%E5%B7%B1%E5%8F%AF%E8%A7%81%E5%BE%AE%E5%8D%9A%E2%80%9D%2C%E4%B8%80%E5%BC%A0%E5%9B%BE%E7%89%87%EF%BC%8C%E4%B8%80%E4%B8%AA%E8%A1%A8%E6%83%85")
print urllib.unquote("[truncated] text=test%20for%20%5B%E5%98%BB%E5%98%BB%5D%20private%20%E5%BE%AE%E5%8D%9A%EF%BC%8C%E6%B5%8B%E8%AF%95%E2%80%9C%E4%BB%85%E8%87%AA%E5%B7%B1%E5%8F%AF%E8%A7%81%E5%BE%AE%E5%8D%9A%E2%80%9D%2C%E4%B8%80%E5%BC%A0%E5%9B%BE%E7%89%87%EF%BC%8C%E4%B8%80%E4%B8%AA")
