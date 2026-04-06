cat > ~/record_demo.sh << 'EOF'
#!/bin/bash
echo "🎬 Запись демонстрации..."
echo "Через 3 секунды начнётся запись экрана"
sleep 3
ffmpeg -f x11grab -video_size 1280x720 -i :0.0 -r 30 -t 60 /tmp/demo.mp4
echo "✅ Видео сохранено в /tmp/demo.mp4"
EOF

chmod +x ~/record_demo.sh
