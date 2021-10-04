# 開發紀錄（week3）
###### tags: `數位音樂訊號分析`

## 作業要求

1. 將 sine wave 合成器改成方波、三角波、鋸齒波
2. 將開發紀錄與 GitHub 連結貼到作業區
3. 截止日期：Oct 5, 2021 14:00 之前

----

## 波形

![](https://i.imgur.com/VjGs9jI.png)

### Sine

$$
y = sin(\theta)
$$

```c++=
std::sin(currentAngle);
```

### Square

$$
y = sgn(sin(\theta))
$$


```c++=
std::sin(currentAngle) > 0 ? 1 : 0;
```

### Triangle

$$
y = arcsin(sin(\theta))
$$

```c++=
std::asin(sin(currentAngle));
```

### Sawtooth

$$
y = arctan(tan(\theta))
$$

```c++=
std::atan(tan(currentAngle));
```

----

## 踩雷的點

- 新增檔案必須在 Projucer 進行，使用 xcode 會讀不到檔案
- `AudioPluginHost.app` 必須額外編譯，預設是沒有的
- 在 build 完之後必須自己從 option 或是資料夾中匯入編譯完成的 vst 檔案
