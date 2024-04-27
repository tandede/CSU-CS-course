import json
import sys
import tkinter as tk
from urllib.request import urlopen, Request
from urllib.error import URLError
from urllib.parse import urlencode, quote_plus
import pygame
from io import BytesIO

API_KEY = 'bCV1HZdfiOeUIUFhfqaNhfGL'
SECRET_KEY = 'P2XulgdcP605UPqnW5K1EjgvxMFTudX2'

FORMATS = {3: "mp3", 4: "pcm", 5: "pcm", 6: "wav"}
TTS_URL = 'http://tsn.baidu.com/text2audio'

class DemoError(Exception):
    pass

# Define IS_PY3, TOKEN_URL, and SCOPE here
IS_PY3 = sys.version_info.major == 3
TOKEN_URL = 'http://aip.baidubce.com/oauth/2.0/token'
SCOPE = 'audio_tts_post'  # 有此scope表示有tts能力，没有请在网页里勾选

class TextToSpeechApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Text to Speech")

        self.text_entry = tk.Entry(root, width=40)
        self.text_entry.pack(pady=10)

        self.speak_button = tk.Button(root, text="喇叭", command=self.speak_text)
        self.speak_button.pack(pady=10)

        # Initialize pygame mixer for audio playback
        pygame.mixer.init()

    def speak_text(self):
        text = self.text_entry.get()
        if text:
            self.text_to_speech(text)
        else:
            print("请输入文本")

    def text_to_speech(self, text):
        token = self.fetch_token()
        tex = quote_plus(text)
        params = {'tok': token, 'tex': tex, 'per': PER, 'spd': SPD, 'pit': PIT, 'vol': VOL, 'aue': AUE, 'cuid': CUID,
                  'lan': 'zh', 'ctp': 1}
        data = urlencode(params)
        req = Request(TTS_URL, data.encode('utf-8'))
        has_error = False
        try:
            f = urlopen(req)
            result_str = f.read()

            headers = dict((name.lower(), value) for name, value in f.headers.items())
            has_error = ('content-type' not in headers.keys() or headers['content-type'].find('audio/') < 0)
        except URLError as err:
            print('tts http response http code : ' + str(err.code))
            result_str = err.read()
            has_error = True

        if has_error:
            print("tts api  error")
        else:
            self.play_audio(result_str)

    def fetch_token(self):
        print("获取token开始")
        params = {'grant_type': 'client_credentials',
                  'client_id': API_KEY,
                  'client_secret': SECRET_KEY}
        post_data = urlencode(params)
        if IS_PY3:
            post_data = post_data.encode('utf-8')
        req = Request(TOKEN_URL, post_data)
        try:
            f = urlopen(req, timeout=5)
            result_str = f.read()
        except URLError as err:
            print('token http response http code : ' + str(err.code))
            result_str = err.read()

        if IS_PY3:
            result_str = result_str.decode()

        result = json.loads(result_str)
        if 'access_token' in result.keys() and 'scope' in result.keys():
            if not SCOPE in result['scope'].split(' '):
                raise DemoError('scope不正确')
            print('成功获取token: %s ; 过期时间（秒）: %s' % (result['access_token'], result['expires_in']))
            return result['access_token']
        else:
            raise DemoError('API_KEY或SECRET_KEY可能不正确: token响应中找不到access_token或scope')

    def play_audio(self, audio_data):
        audio_stream = BytesIO(audio_data)
        pygame.mixer.music.load(audio_stream)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            continue

if __name__ == '__main__':
    PER = 1
    SPD = 5
    PIT = 5
    VOL = 5
    AUE = 3
    CUID = "123456PYTHON"

    root = tk.Tk()
    app = TextToSpeechApp(root)
    root.mainloop()
