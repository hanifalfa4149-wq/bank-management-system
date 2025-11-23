# Bank Management System

[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://www.cprogramming.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Sistem Manajemen Bank sederhana yang dibangun dengan bahasa C untuk memenuhi tugas mata kuliah Algoritma dan Pemrograman.

## 📋 Daftar Isi
- [Fitur Utama](#-fitur-utama)
- [Persyaratan Sistem](#-persyaratan-sistem)
- [Instalasi](#-instalasi)
- [Cara Penggunaan](#-cara-penggunaan)
- [Struktur Proyek](#-struktur-proyek)
- [Anggota Tim](#-anggota-tim)
- [Lisensi](#-lisensi)

## ✨ Fitur Utama

### 🏛️ Admin
- Login dengan kredensial admin
- Membuat akun nasabah baru
- Melihat daftar semua akun
- Mengelola akun (blokir/buka blokir)
- Melihat log aktivitas sistem
- Generate laporan transaksi

### 👤 Nasabah
- Login dengan ID dan password
- Melihat informasi akun
- Melakukan transaksi:
  - Setor tunai
  - Tarik tunai
  - Transfer ke rekening lain
- Melihat riwayat transaksi
- Mengubah password

## 💻 Persyaratan Sistem
- Compiler C (GCC/MinGW)
- Sistem Operasi: Windows/Linux/macOS
- Minimal RAM: 2GB
- Ruang Disk: 50MB

## 🚀 Instalasi

1. Clone repository ini:
   ```bash
   git clone https://github.com/username/bank-management-system.git
   cd bank-management-system
   ```

2. Compile program:
   ```bash
   gcc -o bank_system src/*.c -Iinclude
   ```

3. Jalankan program:
   ```bash
   ./bank_system
   ```

## 🎮 Cara Penggunaan

1. **Menu Utama**
   - Pilih "Customer Login" untuk masuk sebagai nasabah
   - Pilih "Admin Login" untuk masuk sebagai admin
   - Gunakan opsi "Simpan Data" untuk menyimpan perubahan
   - Gunakan opsi "Muat Data" untuk memuat data yang tersimpan

2. **Login Admin**
   - Username: `ADMIN`
   - Password: `admin123`

## 📁 Struktur Proyek

```
bank-management-system/
├── data/
│   ├── data_bank.txt     # Database akun nasabah
│   └── audit_log.txt     # Log aktivitas sistem
├── include/             # File header
│   ├── account.h
│   ├── admin.h
│   ├── audit.h
│   ├── bank.h
│   ├── menu.h
│   ├── operations.h
│   ├── storage.h
│   └── utils.h
├── src/                 # Source code
│   ├── account.c
│   ├── admin.c
│   ├── audit.c
│   ├── bank.c
│   ├── main.c
│   ├── menu.c
│   ├── operations.c
│   ├── storage.c
│   └── utils.c
└── README.md            # Dokumentasi ini
```

## 👥 Anggota Tim

| NIM | Nama | Peran |
|-----|------|-------|
| 25071104149 | Hanif Alfa Rizki | Tech Lead |
| 1234567891 | Nama Anggota 1 | Developer |
| 1234567892 | Nama Anggota 2 | Developer |
| 1234567888 | Nama Anggota 2 | dokumentasi |
| 1515151515 | Nama Anggota 2 | PPT Builder |

## 📄 Lisensi

Proyek ini dilisensikan di bawah [MIT License](LICENSE).

---

Dibuat dengan ❤️ untuk memenuhi tugas mata kuliah pemograman dasar
