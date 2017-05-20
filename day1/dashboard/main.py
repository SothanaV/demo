from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit

app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/")
def hello():
	return render_template('index.html')


@app.route('/<i>/<user>/<temp>/<humi>')
def add(i,user="",temp=0,humi=0):
	socketio.emit('s2c', 
		{	
			'i':i,
			'user': user,
			'temp': temp,
			'humi': humi
		})
	return "OK"

if __name__ == "__main__":
	#app.run(host='0.0.0.0', debug=False)
	socketio.run(app)