import json
import sys
import tkinter as tk
from tkinter import filedialog
from urllib.request import urlopen, Request
from urllib.error import URLError
from urllib.parse import urlencode, quote_plus
import pygame
from io import BytesIO
import threading
import queue

API_KEY = 'bCV1HZdfiOeUIUFhfqaNhfGL'
SECRET_KEY = 'P2XulgdcP605UPqnW5K1EjgvxMFTudX2'

FORMATS = {3: "mp3", 4: "pcm", 5: "pcm", 6: "wav"}
TTS_URL = 'http://tsn.baidu.com/text2audio'

class DemoError(Exception):
    pass

IS_PY3 = sys.version_info.major == 3
TOKEN_URL = 'http://aip.baidubce.com/oauth/2.0/token'
SCOPE = 'audio_tts_post'

class TextToSpeechApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Text to Speech")

        self.text_entry = tk.Entry(root, width=40)
        self.text_entry.pack(pady=10)

        self.speak_button = tk.Button(root, text="喇叭", command=self.speak_text)
        self.speak_button.pack(pady=10)

        self.create_novel_reading_interface()

        # Initialize pygame mixer for audio playback
        pygame.mixer.init()

        # Configure number of channels
        self.num_channels = 10
        self.channels = [None] * self.num_channels
        self.channel_lock = threading.Lock()

    def create_novel_reading_interface(self):
        self.novel_frame = tk.Frame(self.root)
        self.novel_frame.pack(pady=20)

        self.speech_params_frame = tk.Frame(self.root)
        self.speech_params_frame.pack(pady=10)

        self.per_label = tk.Label(self.speech_params_frame, text="音色:")
        self.per_label.grid(row=0, column=0)
        self.per_slider = tk.Scale(self.speech_params_frame, from_=0, to=4, orient=tk.HORIZONTAL)
        self.per_slider.set(1)
        self.per_slider.grid(row=0, column=1)

        self.spd_label = tk.Label(self.speech_params_frame, text="语速:")
        self.spd_label.grid(row=0, column=2)
        self.spd_slider = tk.Scale(self.speech_params_frame, from_=0, to=9, orient=tk.HORIZONTAL)
        self.spd_slider.set(5)
        self.spd_slider.grid(row=0, column=3)

        self.pit_label = tk.Label(self.speech_params_frame, text="音调:")
        self.pit_label.grid(row=0, column=4)
        self.pit_slider = tk.Scale(self.speech_params_frame, from_=-9, to=9, orient=tk.HORIZONTAL)
        self.pit_slider.set(5)
        self.pit_slider.grid(row=0, column=5)

        self.vol_label = tk.Label(self.speech_params_frame, text="音量:")
        self.vol_label.grid(row=0, column=6)
        self.vol_slider = tk.Scale(self.speech_params_frame, from_=0, to=15, orient=tk.HORIZONTAL)
        self.vol_slider.set(5)
        self.vol_slider.grid(row=0, column=7)

        self.text_widget = tk.Text(self.novel_frame, wrap="word", height=20, width=50)
        self.text_widget.pack(side=tk.LEFT, fill=tk.BOTH, expand=tk.YES)
        self.scrollbar = tk.Scrollbar(self.novel_frame, command=self.text_widget.yview)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.text_widget.config(yscrollcommand=self.scrollbar.set)

        self.import_button = tk.Button(self.root, text="导入小说", command=self.import_novel)
        self.import_button.pack(pady=10)

        self.speak_imported_button = tk.Button(self.root, text="朗读导入文本", command=self.speak_imported_text)
        self.speak_imported_button.pack(pady=10)

    def speak_text(self):
        text = self.text_entry.get()
        if text:
            # Find an available channel and start speaking
            with self.channel_lock:
                for i in range(self.num_channels):
                    if self.channels[i] is None or not self.channels[i].is_alive():
                        per = self.per_slider.get()
                        spd = self.spd_slider.get()
                        pit = self.pit_slider.get()
                        vol = self.vol_slider.get()

                        self.channels[i] = threading.Thread(target=self.text_to_speech,
                                                            args=(text, per, spd, pit, vol))
                        self.channels[i].start()
                        break
        else:
            print("请输入文本")

    def speak_imported_text(self):
        imported_text = self.text_widget.get(1.0, tk.END)
        if imported_text.strip():
            # Find an available channel and start speaking
            with self.channel_lock:
                for i in range(self.num_channels):
                    if self.channels[i] is None or not self.channels[i].is_alive():
                        per = self.per_slider.get()
                        spd = self.spd_slider.get()
                        pit = self.pit_slider.get()
                        vol = self.vol_slider.get()

                        self.channels[i] = threading.Thread(target=self.text_to_speech,
                                                            args=(imported_text, per, spd, pit, vol))
                        self.channels[i].start()
                        break
        else:
            print("导入文本为空")

    def text_to_speech(self, text, per, spd, pit, vol):
        token = self.fetch_token()
        tex = quote_plus(text)
        params = {'tok': token, 'tex': tex, 'per': per, 'spd': spd, 'pit': pit, 'vol': vol, 'aue': AUE, 'cuid': CUID,
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

    def import_novel(self):
        file_path = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
        if file_path:
            with open(file_path, 'r', encoding='utf-8') as file:
                content = file.read()
                self.text_widget.delete(1.0, tk.END)  # Clear previous content
                self.text_widget.insert(tk.END, content)

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
