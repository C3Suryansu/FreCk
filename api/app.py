from flask import Flask, render_template, request, jsonify, json
import base64

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/scan', methods = ['GET','POST'])
def scan():
    if request.method == 'POST':
        request_data = json.loads(request.data)
        byte = request_data['input']
        # decodeit = open('./static/img.jpeg', 'wb')
        # decodeit.write(base64.b64decode((byte)))
        # decodeit.close()
        return jsonify({"code":" 99.98"})

    return jsonify({'flevel':"0"})

if __name__ == '__main__':
    app.run()
