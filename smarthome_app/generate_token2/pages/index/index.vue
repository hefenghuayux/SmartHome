<template>
  <view class="content">
    <view class="sensor-info">
      <view class="sensor-item">温度: <span class="value">{{ temp }}℃</span></view>
      <view class="sensor-item">湿度: <span class="value">{{ wet }}%</span></view>
      <view class="sensor-item">红外: <span class="value">{{ hongwai }}</span></view>
      <view class="sensor-item">亮度: <span class="value">{{ light }}</span></view>
    </view>

    <view class="led-control">
      <view class="led-label">LED控制</view>
      <switch :checked="led" @change="onLedSwitch" class="led-switch" />
    </view>



    <view class="text-area">
      <text class="title">{{ title }}</text>
    </view>
  </view>
</template>

<script>
	const {
		createCommonToken
	} = require('@/key.js')
	export default {
		data() {
			return {
				temp: '',
				wet: '',
				hongwai: '',
				light: '',
				led: true,
				title: '',
				token: '',
				title:'智能家居'
			}
		},
		onLoad() {
			const params = {
				author_key: '7Fveu0CdMu0AN+WPzoh+RxygbGAxdh2zax/ZBahL+OJYrGODI7OiJM0UqCYRiwsC',
				version: '2022-05-01',
				user_id: '412824',
			}

			this.token = createCommonToken(params);
		},
		onShow(){
			setInterval(()=>{
				this.fetchDevData();
			},3000)
		},
		methods: {
			fetchDevData() {
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/query-device-property', //仅为示例，并非真实接口地址。
					method:'GET',
					data: {			
						product_id:'ta2nYzRAmN',
						device_name:'d1'
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: (res) => {
					
						
						this.hongwai=res.data.data[0].value;
						this.led=res.data.data[1].value==='true';
						this.light=res.data.data[2].value;
						this.temp=res.data.data[3].value;
						this.wet=res.data.data[4].value;
						
					}
				});

			},
			onLedSwitch(event) {
				console.log(event.detail.value);
				let value =event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //仅为示例，并非真实接口地址。
					method:'POST',
					data: {			
						product_id:'ta2nYzRAmN',
						device_name:'d1',
						params:{"led":value}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: (res) => {
					console.log('LED'+(value?'ON':'OFF'));
						
					}
				});
			
			},
		}
	}
</script>

<style>
.content {
  padding: 20px;
  background-color: #f9f9f9;
  font-family: Arial, sans-serif;
}

.sensor-info {
  margin-bottom: 20px;
}

.sensor-item {
  font-size: 18px;
  margin: 10px 0;
  color: #333;
}

.value {
  font-weight: bold;
  color: #007aff;
}

.led-control {
  display: flex;
  align-items: center;
  margin-bottom: 20px;
}

.led-label {
  font-size: 18px;
  color: #333;
  margin-right: 10px;
}

.led-switch {
  transform: scale(1.2); /* 放大开关 */
}



.text-area {
  margin-top: 20px;
  text-align: center;
}

.title {
  font-size: 22px;
  font-weight: bold;
  color: #333;
  line-height: 1.5;
}
</style>