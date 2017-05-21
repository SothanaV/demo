from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
import json

app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/")
def hello():
	return render_template('index.html')

@app.route("/data/<node_id>/<temp>/<humi>/")
def get(node_id,temp,humi):
	data={ 
		"node_id":node_id,
		"temp": temp,
		"humi": humi
	}
	print json.dumps(data, sort_keys=True)
	socketio.emit('s2c', json.dumps(data), broadcast=True)
	return "OK"

@socketio.on('c2s')
def handle_message(message):
	emit('s2c',message, broadcast=True)
	print(message)

if __name__ == "__main__":
    #app.run(host='0.0.0.0', debug=False)
    socketio.run(app)