import requests
import json

API_KEY = 'bCV1HZdfiOeUIUFhfqaNhfGL'
SECRET_KEY = 'P2XulgdcP605UPqnW5K1EjgvxMFTudX2'

def main():
        
    url = "https://aip.baidubce.com/rpc/2.0/tts/v1/query?access_token=" + get_access_token()
    
    payload = json.dumps({
        "task_ids": [
            "xxxxxxxxxxxxxxxxxx"    #create获取的task_id
        ]
    })
    headers = {
        'Content-Type': 'application/json',
        'Accept': 'application/json'
    }
    
    response = requests.request("POST", url, headers=headers, data=payload)
    
    print(response.text)
    

def get_access_token():
    """
    使用 AK，SK 生成鉴权签名（Access Token）
    :return: access_token，或是None(如果错误)
    """
    url = "https://aip.baidubce.com/oauth/2.0/token"
    params = {"grant_type": "client_credentials", "client_id": API_KEY, "client_secret": SECRET_KEY}
    return str(requests.post(url, params=params).json().get("access_token"))

if __name__ == '__main__':
    main()
