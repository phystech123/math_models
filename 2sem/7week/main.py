import plotly.graph_objects as go
import numpy as np
import pandas as pd

# Генерация данных
dfX = pd.read_csv("data/0.csv")
time = dfX["i"][::5] # Массив времени (ось X)
coordinate = dfX["x"][::5]               # Координата (ось Y)

# Создание кадров анимации
frames = [
    go.Frame(
        data=[
            go.Scatter(
                x=time[:k+1], 
                y=coordinate[:k+1],
                mode="markers",  # Точки + линия
                marker=dict(size=10, color="#FF4C29"),
                line=dict(width=2, color="#2B3467")
            )
        ],
        name=f"frame_{k}"
    ) 
    for k in range(len(time))
]

# Настройка фигуры
fig = go.Figure(
    data=[
        go.Scatter(
            x=[], 
            y=[],
            mode="markers",
            marker=dict(size=10),
            line=dict(width=2))
    ],
    frames=frames,
    layout=go.Layout(
        title="Анимация движения точки",
        xaxis=dict(range=[0, 10], title="Время (секунды)"),
        yaxis=dict(range=[-2.5, 2.5], title="Координата"),
        updatemenus=[{
            "type": "buttons",
            "buttons": [
                {
                    "label": "▶️ Старт",
                    "method": "animate",
                    "args": [
                        None, 
                        {
                            "frame": {"duration": 30, "redraw": True},
                            "fromcurrent": True
                        }
                    ]
                },
                {
                    "label": "⏹️ Стоп",
                    "method": "animate",
                    "args": [
                        [None], 
                        {"mode": "immediate"}
                    ]
                }
            ],
            "showactive": False
        }],
        showlegend=False
    )
)

# Отображение в Jupyter Notebook
fig.show()