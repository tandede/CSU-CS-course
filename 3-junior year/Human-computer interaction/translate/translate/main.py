import json
import sys
import tkinter as tk
from tkinter import ttk
from urllib.request import urlopen, Request
from urllib.error import URLError
from urllib.parse import urlencode, quote_plus
import pygame
from io import BytesIO
from translate import Translator
from PIL import Image, ImageTk

# 百度云 API 相关信息
API_KEY = 'bCV1HZdfiOeUIUFhfqaNhfGL'
SECRET_KEY = 'P2XulgdcP605UPqnW5K1EjgvxMFTudX2'
TOKEN_URL = 'http://aip.baidubce.com/oauth/2.0/token'
SCOPE = 'audio_tts_post'

FORMATS = {3: "mp3", 4: "pcm", 5: "pcm", 6: "wav"}
TTS_URL = 'http://tsn.baidu.com/text2audio'

# 是否为 Python 3
IS_PY3 = sys.version_info.major == 3

# Definition of DemoError class
class DemoError(Exception):
    pass

# Initialize pygame mixer for audio playback
pygame.mixer.init()

class TranslationApp:
    def __init__(self, root):
        self.root = root
        self.root.title("智能翻译")

        # 设置窗口背景颜色
        self.root.configure(bg="#ADD870")

        self.create_widgets()

    def create_widgets(self):
        # 在 Canvas 上添加其他组件
        self.text_var = tk.StringVar()
        self.text_entry = tk.Entry(self.root, textvariable=self.text_var, width=50)
        self.text_entry.grid(row=0, column=0, padx=10, pady=50)

        self.translate_button = tk.Button(self.root, text="翻译", command=self.translate_text,bg="#1E90FF", fg="white")
        self.translate_button.grid(row=0, column=1, padx=10, pady=10)

        # 图片按钮 - 输入框旁边
        self.image_path_input = "img/laba.jpg"  
        self.laba_img_input = Image.open(self.image_path_input)
        self.laba_img_input = ImageTk.PhotoImage(self.laba_img_input.resize((20, 20), Image.LANCZOS))
        self.laba_button_input = tk.Button(self.root, image=self.laba_img_input, text="", compound=tk.LEFT, command=self.speak_input_text,bg="#FFFACD", fg="white")
        self.laba_button_input.grid(row=0, column=2, padx=20, pady=20)

        self.from_lang_label = tk.Label(self.root, text="源语言:")
        self.from_lang_label.grid(row=1, column=0, padx=20, pady=20)

        self.from_lang_combobox = ttk.Combobox(self.root, values=["auto", "zh", "en"], state="readonly")
        self.from_lang_combobox.set("auto")
        self.from_lang_combobox.grid(row=1, column=1, padx=20, pady=20)

        self.to_lang_label = tk.Label(self.root, text="目标语言:")
        self.to_lang_label.grid(row=2, column=0, padx=20, pady=20)

        self.to_lang_combobox = ttk.Combobox(self.root, values=["zh", "en"], state="readonly")
        self.to_lang_combobox.set("en")
        self.to_lang_combobox.grid(row=2, column=1, padx=20, pady=20)

        self.translation_label = tk.Label(self.root, text="翻译结果:")
        self.translation_label.grid(row=3, column=0, padx=20, pady=20)

        self.translation_text = tk.Text(self.root, height=5, width=40)
        self.translation_text.grid(row=3, column=1, padx=20, pady=20)

        # 图片按钮 - 输出框旁边
        self.image_path_output = "img/laba.jpg"  # 替换为你的图片路径
        self.laba_img_output = Image.open(self.image_path_output)
        self.laba_img_output = ImageTk.PhotoImage(self.laba_img_output.resize((20, 20), Image.LANCZOS))
        self.laba_button_output = tk.Button(self.root, image=self.laba_img_output, text="", compound=tk.LEFT, command=self.speak_output_text,bg="#FFFACD", fg="white")
        self.laba_button_output.grid(row=3, column=2, padx=5, pady=10)

    def translate_text(self):
        text_to_translate = self.text_var.get()

        if not text_to_translate:
            self.translation_text.delete(1.0, tk.END)
            self.translation_text.insert(tk.END, "请输入要翻译的文本")
            return

        # 获取源语言
        from_lang = self.from_lang_combobox.get()

        # 获取目标语言
        target_lang = self.to_lang_combobox.get()

        # 进行翻译
        translated_text = self.translate_text_with_translate(text_to_translate, from_lang, target_lang)

        if translated_text:
            self.translation_text.delete(1.0, tk.END)
            self.translation_text.insert(tk.END, translated_text)
        else:
            self.translation_text.delete(1.0, tk.END)
            self.translation_text.insert(tk.END, "翻译失败")

    def translate_text_with_translate(self, text, source_language, target_language):
        translator = Translator(to_lang=target_language, from_lang=source_language)

        try:
            translation = translator.translate(text)
            return translation
        except Exception as e:
            print("翻译出现错误:", e)
            return None

    def speak_input_text(self):
        text_to_speak = self.text_var.get()
        self.text_to_speech(text_to_speak)

    def speak_output_text(self):
        text_to_speak = self.translation_text.get(1.0, tk.END)
        self.text_to_speech(text_to_speak)

    def text_to_speech(self, text):
        # 调用百度云文字转语音 API
        token = self.fetch_token()
        tex = quote_plus(text)
        params = {'tok': token, 'tex': tex, 'per': 1, 'spd': 5, 'pit': 5, 'vol': 5, 'aue': 3, 'cuid': "123456PYTHON", 'lan': 'zh', 'ctp': 1}
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
            # print('成功获取token: %s ; 过期时间（秒）: %s' % (result['access_token'], result['expires_in']))
            return result['access_token']
        else:
            raise DemoError('API_KEY或SECRET_KEY可能不正确: token响应中找不到access_token或scope')

    def play_audio(self, audio_data):
        audio_stream = BytesIO(audio_data)
        pygame.mixer.music.load(audio_stream)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            continue

if __name__ == "__main__":
    root = tk.Tk()
    app = TranslationApp(root)
    root.mainloop()
