from flask import Flask, render_template, request, jsonify, json
import base64
from keras.models import load_model
import numpy as np
import cv2
from PIL import Image
import io

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/scan', methods = ['GET','POST'])
def scan():
    if request.method == 'POST':
        request_data = json.loads(request.data)
        b_str = request_data['input']
        """
        # This part isn't required anymore, commenting for later uses.
        # decodeit = open('./static/img.jpeg', 'wb')
        # decodeit.write(base64.b64decode((byte)))
        # decodeit.close()
        """

        # Convert base64 string to img array

        # img = Image.open(io.BytesIO(base64.decodebytes(bytes(b_str, "utf-8"))))
        # img = np.array(img)

        # Image prediction for image stored in variable img

        # model = load_model('model.h5')
        # img = cv2.resize(img, (256, 256))
        # img = np.expand_dims(img, axis = 0)
        # res_arr = model.predict(img)
        # slabel = np.argmax(res_arr)
        # if slabel == 0:
        #     status = "Fresh"
        #     conf_score = res_arr[0]
        # else:
        #     status = "Spoilt"
        #     conf_score = res_arr[1]
        
        return jsonify({"code":" 99.98"})

    return jsonify({'flevel':"0"})

if __name__ == '__main__':
    app.run()
